import CMD.BROADCAST
import Print.printError
import Print.printMessage
import java.io.DataInputStream
import java.io.DataOutputStream
import java.io.IOException
import kotlin.system.exitProcess

const val MESSAGE_ELEVATION_START = "elevation in progress"
const val MESSAGE_ELEVATION_FINISH = "current level : "
const val MESSAGE_BROADCAST = "message "
const val MESSAGE_DEATH = "death"

object Message {

	fun sendMessage(msg: String) = try {
		msg.forEach { DataOutputStream(Env.client.getOutputStream()!!).writeByte(it.toInt()) }
	} catch (e: IOException) {
		printError("${e.message}")
	}

	fun getMessage(): String {
		val msg = StringBuffer("")

		try {
			val input = DataInputStream(Env.client.getInputStream()!!)
			while (true) {
				val c = input.read().toChar()
				if (c == '\n') break
				msg.append(c)
			}
		} catch (e: IOException) { printError("${e.message}") } catch (e: OutOfMemoryError) { printError("${e.message}") } catch (e: Exception) {
			printError("${e.message}")
		}
		val res = msg.toString()
		if (res == MESSAGE_DEATH) {
			printMessage(MESSAGE_DEATH)
			exitProcess(0)
		}

		if (res.startsWith(MESSAGE_BROADCAST))
			handleBroadcast(messageToBroadcast(res))
		if (res.startsWith(MESSAGE_ELEVATION_FINISH))
			handleElevationFinish(res.substring(MESSAGE_ELEVATION_FINISH.length, res.length))
		return res
	}

	fun getMessageComing(msg: String): Broadcast {
		println("getMessageComing")
		Message.sendMessage(BROADCAST + msg + "\n")
		val message = getMessage()
		if (message.startsWith(MESSAGE_BROADCAST)) {
			val br = messageToBroadcast(message)
			if (br.id != Env.id && br.level == Env.level && br.code == BROADCASTTYPE.COMING.ordinal)
				return br
		}
		try {
			Thread.sleep(2000)
		} catch (e: Exception) {
			println("THREAD EX ${e.message}")
		}
		return getMessageComing(msg)
	}

	private fun handleBroadcast(br: Broadcast) {
		if (br.id != Env.id && br.level == Env.level && br.code == BROADCASTTYPE.CALLING.ordinal) {
			Env.hasBeenCalled[Env.level] = br.origin
			println("handleBroadcast Env.hasBeenCalled[Env.level] ${Env.hasBeenCalled[Env.level]} - Env.level ${Env.level}")
		}
	}

	private fun handleElevationFinish(res: String) {
		try {
			Env.level = res.toInt()
		} catch (e: NumberFormatException) {
			printError(MESSAGE_ELEVATION_FINISH)
		}
		Env.hasBeenCalled[Env.level] = -1
	}

}