import Print.printError
import java.io.DataOutputStream
import java.io.IOException
import java.net.Socket
import java.net.UnknownHostException
import java.util.*


class Env {
	private val WELCOME = "WELCOME"

    var level = 1
	val id = Random().nextInt(99 - 10 + 1) + 10

    var client : Socket = Socket()
    var name : String = ""
    var port : Int = 0
    var host : String = ""

	var hasBeenCalled = mutableMapOf(1 to -1, 2 to -1, 3 to -1, 4 to -1, 5 to -1, 6 to -1, 7 to -1, 8 to -1)

    var nbClient : Int = 0
    var x : Int = 0
    var y : Int = 0


	fun init(env: Env, args: Array<String>) {
        initArg(args)
		if (!hostAvailabilityCheck())
			return
        initSocket()
		initWelcome(env)
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

	private fun initWelcome(env: Env) {
        val out = DataOutputStream(client.getOutputStream()!!)
		Message.getMessage(env).also { if (it != WELCOME) printError(WELCOME) }
        name.forEach { out.writeByte(it.toInt()) }.also { out.writeByte('\n'.toInt()) }
		nbClient = try {
			Message.getMessage(env).toInt()
		} catch (e: NumberFormatException) {
			printError("nbr client "); 0
		}
		val xy = (Message.getMessage(env).split(" ").map { it.trim() }).also { if (it.size != 2) printError("x y") }

        x = try { xy[0].toInt() } catch (e : NumberFormatException) { printError("x") ; 0 }
        y = try { xy[1].toInt()} catch (e : NumberFormatException) { printError("y") ; 0 }
    }

	private fun hostAvailabilityCheck(): Boolean {
		val s = Socket(host, port)
		var available = true
		try {
			if (s.isConnected) {
				s.close()
			}
		} catch (e: UnknownHostException) { // unknown host
			available = false
		} catch (e: IOException) { // io exception, service probably not running
			available = false
		} catch (e: NullPointerException) {
			available = false
		}


		return available
	}

}