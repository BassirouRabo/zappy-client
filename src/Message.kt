import Print.printError
import Print.printMessage
import java.io.DataInputStream
import java.io.DataOutputStream
import java.io.IOException
import kotlin.system.exitProcess

object Message {
    private const val DEATH = "DEATH"
    private const val INCANTATION = "elevation in progress current level : "
    private const val MESSAGE_BROADCAST = "message "
    private const val MESSAGE_DEATH = "death"

    private fun parse(msg: String) {
        if (msg == DEATH) {
            printError(DEATH)
        } else if (msg.startsWith(INCANTATION, false)) {
            try { Env.level = msg.substring(INCANTATION.length, msg.length).toInt() } catch (e : NumberFormatException) { printError(INCANTATION) }
        }
    }

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

        } catch (e: IOException) { printError("${e.message}") }

        var res = msg.toString()

        if (res.startsWith(MESSAGE_BROADCAST)) {
            res = res.substring(MESSAGE_BROADCAST.length, res.length)
            res.split(",").map { it.trim() }.also {
                if (it.size != 2) printError(MESSAGE_DEATH)

                val origin = try {
                    it[0].toInt()
                } catch (e: NumberFormatException) {
                    printError(MESSAGE_BROADCAST); 0
                }

                val message = try {
                    it[1].toInt()
                } catch (e: NumberFormatException) {
                    printError(MESSAGE_BROADCAST); 0
                }

                Env.broadcast.add(Pair(message, origin))
            }
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