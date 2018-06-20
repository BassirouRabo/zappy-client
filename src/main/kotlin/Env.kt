import Print.printError
import java.io.DataInputStream
import java.io.DataOutputStream
import java.io.IOException
import java.net.Socket
import java.util.*

object Env {
    private const val WELCOME = "WELCOME"

    var level = 1
	val id = Random().nextInt(99 - 10 + 1) + 10

    var client : Socket = Socket()
    var name : String = ""
    var port : Int = 0
    var host : String = ""

    var broadcastCallingReceive = false
	var canMove = true

    var nbClient : Int = 0
    var x : Int = 0
    var y : Int = 0


    fun init(action: Action, args: Array<String>) {
        initArg(args)
        initSocket()
        initWelcome(action)
    }

    private fun initArg(args: Array<String>) {
        name = args[0]
        host = args[2]
        port = try { args[1].toInt() } catch (e : NumberFormatException) { 0 }
        if (port in 0..1024) printError("Port cant't be [0 - 1023]")
    }

    private fun initSocket() {
        try {
            client = Socket(host, port)
        }catch (e: IOException) {printError(e.message ?: " Socket {${e.message}}") }
    }

    private fun initWelcome(action: Action) {
        val out = DataOutputStream(client.getOutputStream()!!)

        Message.getMessage(action).also { if (it != WELCOME) printError(WELCOME) }
        name.forEach { out.writeByte(it.toInt()) }.also { out.writeByte('\n'.toInt()) }
        nbClient = try { Message.getMessage(action).toInt() } catch (e : NumberFormatException) { printError("nbr client ") ; 0 }

        val xy = (Message.getMessage(action).split(" ").map { it.trim() }).also {  if (it.size != 2) println("x y") }

        x = try { xy[0].toInt() } catch (e : NumberFormatException) { printError("x") ; 0 }
        y = try { xy[1].toInt()} catch (e : NumberFormatException) { printError("y") ; 0 }
    }

}