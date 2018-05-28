import java.net.*
import java.io.*

fun main(args: Array<String>) {
    val serverSocket: ServerSocket

    serverSocket = ServerSocket(args[0].toInt())
    var cardsList = listOf("hi", true, 24)
    var cardsList1 : List<String>  = listOf("hi", "hello")

    while (true) {
        try {
            println("Waiting for client on port " + serverSocket.localPort + "...")
            val server = serverSocket.accept()

            println("Just connected to " + server.remoteSocketAddress)
            val `in` = DataInputStream(server.getInputStream())

            println(`in`.readUTF())
            val out = DataOutputStream(server.getOutputStream())
            out.writeUTF("Thank you for connecting to " + server.localSocketAddress +"\nGoodbye!")
            server.close()

        } catch (s: SocketTimeoutException) {
            println("Socket timed out!")
            break
        } catch (e: IOException) {
            e.printStackTrace()
            break
        }

    }
}