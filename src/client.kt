// File Name GreetingClient.java
import java.net.*
import java.io.*

    fun main(args: Array<String>) {
        val serverName = args[0]
        val port = Integer.parseInt(args[1])
        try {
            println("Connecting to $serverName on port $port")
            val client = Socket(serverName, port)

            println("Just connected to " + client.remoteSocketAddress)
            val outToServer = client.getOutputStream()
            val out = DataOutputStream(outToServer)

            out.writeUTF("Hello from " + client.localSocketAddress)
            val inFromServer = client.getInputStream()
            val `in` = DataInputStream(inFromServer)

            println("Server says " + `in`.readUTF())
            client.close()
        } catch (e: IOException) {
            e.printStackTrace()
        }

    }