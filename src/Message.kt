import Print.printError
import java.io.DataInputStream
import java.io.DataOutputStream
import java.io.IOException

object Message {
    private const val DEATH = "DEATH"
    private const val INCANTATION = "elevation in progress current level : "

    private fun parse(msg: String) {
        if (msg == DEATH) {
            printError(DEATH)
        } else if (msg.startsWith(INCANTATION, false)) {
            try { Env.level = msg.substring(INCANTATION.length, msg.length).toInt() } catch (e : NumberFormatException) { printError(INCANTATION) }
        }
    }

    fun getMessage() : String {
        var msg = ""

        try {
            val input = DataInputStream(Env.client.getInputStream()!!)
            while (true)
            {
                val c = input.read().toChar()
                if (c == '\n') break
                msg += c
            }

        } catch (e: IOException) { printError("${e.message}") }

        return msg
    }

    fun sendMessage(msg: String) = try {
        msg.forEach { DataOutputStream(Env.client.getOutputStream()!!).writeByte(it.toInt()) }
    } catch (e: IOException) {
        printError("${e.message}")
    }
}