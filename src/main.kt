import java.io.DataOutputStream
import java.io.IOException
import java.net.Socket

fun main(args: Array<String>) {
    args.forEach { println(it) }
    val serverName = args[0]
    val port = args[1].toInt()
    try {
        println("Connecting to $serverName on port $port")
        val client = Socket(serverName, port)

        println("Connected to ${client.remoteSocketAddress}")
        val outToServer = client.getOutputStream()
        val out = DataOutputStream(outToServer)

    } catch (e: IOException) {
        println("ERROR ${e.fillInStackTrace()}")
    }
}