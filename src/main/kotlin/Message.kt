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

	fun sendMessage(env: Env, msg: String) = try {
		msg.forEach { DataOutputStream(env.client.getOutputStream()!!).writeByte(it.toInt()) }
	} catch (e: IOException) {
		printError("${e.message}")
	}

	fun getMessage(env: Env): String {
		val msg = StringBuffer("")
		try {
			val input = DataInputStream(env.client.getInputStream()!!)
			while (true) {
				val c = input.read().toChar()
				if (c == '\n') break
				msg.append(c)
			}
		} catch (e: IOException) {
			printError("# ${e.message}")
		} catch (e: OutOfMemoryError) {
			printError("## ${e.message}")
		} catch (e: Exception) {
		}
		val res = msg.toString()
		if (res == MESSAGE_DEATH) {
			printMessage(MESSAGE_DEATH)
			exitProcess(0)
		}
		if (res.startsWith(MESSAGE_BROADCAST))
			handleBroadcast(env, messageToBroadcast(res))
		if (res.startsWith(MESSAGE_ELEVATION_FINISH))
			handleElevationFinish(env, res.substring(MESSAGE_ELEVATION_FINISH.length, res.length))
		return res
	}

	fun getMessageComing(env: Env, msg: String): Broadcast {
		println("getMessageComing")
		Message.sendMessage(env, BROADCAST + msg + "\n")
		val message = getMessage(env)
		if (message.startsWith(MESSAGE_BROADCAST)) {
			val br = messageToBroadcast(message)
			if (br.id != env.id && br.level == env.level && br.code == BROADCASTTYPE.COMING.ordinal)
				return br
		}
		try {
			Thread.sleep(2000)
		} catch (e: Exception) {
			println("THREAD EX ${e.message}")
		}
		return getMessageComing(env, msg)
	}

	private fun handleBroadcast(env: Env, br: Broadcast) {
		if (br.id != env.id && br.level == env.level && br.code == BROADCASTTYPE.CALLING.ordinal) {
			env.hasBeenCalled[env.level] = br.origin
			println("handleBroadcast Env.hasBeenCalled[env.level] ${env.hasBeenCalled[env.level]} - env.level ${env.level}")
		}
	}

	private fun handleElevationFinish(env: Env, res: String) {
		try {
			env.level = res.toInt()
		} catch (e: NumberFormatException) {
			printError(MESSAGE_ELEVATION_FINISH)
		}
		env.hasBeenCalled[env.level] = -1
	}

}