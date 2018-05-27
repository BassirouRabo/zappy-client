import java.net.*
import java.io.*

fun main(args: Array<String>) {
    if (args.size != 3) {
        Print.usage()
        return
    }

    "hello".also { println(it) }.also { println(" hi ") }

    val env = Env
    env.name = args[0]
    env.host = args[2]
    env.port = try { args[1].toInt() } catch (e : NumberFormatException) {
        Print.error_port()
        0
    }
    if (env.port in 1..1024) return

    try {
        println("Trying to connect to ${env.host} on port ${env.name}")
        env.client  = Socket(env.host, env.port)

        println("Name ${env.name} is connected to " + env.client.remoteSocketAddress)
        val outToServer = env.client.getOutputStream()!!
        val out = DataOutputStream(outToServer)

        out.writeUTF("Hello from " + env.client.localSocketAddress)




        val inFromServer = env.client.getInputStream()!!
        val `in` = DataInputStream(inFromServer)

        println("Server says " + `in`.readUTF())
        env.client.close()
    } catch (e: IOException) {
        e.printStackTrace()
    }

}
