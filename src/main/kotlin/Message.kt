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

	fun getMessage(action: Action) : String {
		val msg = StringBuffer("")

		try {
			val input = DataInputStream(Env.client.getInputStream()!!)
			while (true) {
				val c = input.read().toChar()
				if (c == '\n') break
				msg.append(c)
			}
		} catch (e: IOException) { printError("${e.message}") }
		catch (e: OutOfMemoryError) { printError("${e.message}") }

		val res = msg.toString()

		if (res == MESSAGE_DEATH) {
			printMessage(MESSAGE_DEATH)
			exitProcess(0)
		}

		if (res.startsWith(MESSAGE_BROADCAST))
			handleBroadcast(action, res.substring(MESSAGE_BROADCAST.length, res.length))
		if (res.startsWith(MESSAGE_ELEVATION_START))
			return handleElevationStart(action)
		if (res.startsWith(MESSAGE_ELEVATION_FINISH))
			return handleElevationFinish(action, res.substring(MESSAGE_ELEVATION_FINISH.length, res.length))

		return res
	}

	private fun handleBroadcast(action: Action, res: String) {
		val broadcast = messageToBroadcast(res)
		println("ID ${Env.id} handleBroadcast $broadcast")
		if (broadcast.id != Env.id && broadcast.level == Env.level && broadcast.code == BROADCASTTYPE.CALLING.ordinal) {
			Env.broadcastCallingReceive = true
			println("handleBroadcast - broadcastCallingReceive: ${Env.broadcastCallingReceive}")
		}
	}

	private fun handleElevationFinish(action: Action, res: String) : String {
		try {
			Env.level = res.toInt()
		} catch (e: NumberFormatException) {
			printError(MESSAGE_ELEVATION_FINISH)
		}
		Env.canMove = true
		return getMessage(action)
	}

	private fun handleElevationStart(action: Action): String {
		return getMessage(action)
	}

	fun sendMessage(msg: String) = try {
		msg.forEach { DataOutputStream(Env.client.getOutputStream()!!).writeByte(it.toInt()) }
	} catch (e: IOException) { printError("${e.message}") }
}