import Print.printError
import Print.printMessage
import java.io.DataInputStream
import java.io.DataOutputStream
import java.io.IOException
import kotlin.system.exitProcess

const val MESSAGE_ELEVATION_START = "elevation in progress"
const val MESSAGE_ELEVATION_FINISH = "current level : "
const val BROADCAST_CALLING = "calling-"
const val BROADCAST_COMING = "coming-"
const val MESSAGE_BROADCAST = "message "
const val MESSAGE_DEATH = "death"

object Message {

	fun getMessage() : String {
		val msg = StringBuffer("")

		try {
			val input = DataInputStream(Env.client.getInputStream()!!)
			while (true)
			{
				val c = input.read().toChar()
				if (c == '\n') break
				msg.append(c)
			}

		} catch (e: IOException) {
			printError("${e.message}")
		} catch (e: OutOfMemoryError) {
			printError("${e.message}")
		}

		var res = msg.toString()

		if (res.startsWith(MESSAGE_BROADCAST)) {
			//println("MESSAGE_BROADCAST:  $res")
			res = res.substring(MESSAGE_BROADCAST.length, res.length)

			val map = res.split(",").map { it.trim() }
			if (map.size != 2)  printError(MESSAGE_BROADCAST)

			val k = try {
				map[0].toInt()
			} catch (e: NumberFormatException) {
				printError(MESSAGE_BROADCAST); 0
			}
			val text = map[1]

			if (text.startsWith(BROADCAST_CALLING) && k != 0) {

				val message = try {
					text.substring(BROADCAST_CALLING.length, text.length).toInt()
				} catch (e: NumberFormatException) {
					printError("$MESSAGE_BROADCAST $BROADCAST_CALLING"); 0
				}
			//	println("BROADCAST_CALLING message:$message k:$k")
				if (Env.level == message) Env.broadcastCalling = k
			}

			if (text.startsWith(BROADCAST_COMING)) {
				val message = try {
					text.substring(BROADCAST_COMING.length, text.length).toInt()
				} catch (e: NumberFormatException) {
					printError("$MESSAGE_BROADCAST $BROADCAST_COMING"); 0
				}
				println("BROADCAST_COMING message:$message k:$k - ${Env.broadcastComing + 1}")
				if (k == 0 && message == Env.level) Env.broadcastComing++

			}

			return getMessage()
		}

		if (res == MESSAGE_DEATH) {
			printMessage(MESSAGE_DEATH)
			exitProcess(0)
		}
		return res
	}

	fun sendMessage(msg: String) = try {
		msg.forEach { DataOutputStream(Env.client.getOutputStream()!!).writeByte(it.toInt()) }
	} catch (e: IOException) {
		printError("${e.message}")
	}
}