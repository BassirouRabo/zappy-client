import Print.printError
import java.net.*
import java.io.*

fun main(args: Array<String>) {
    if (args.size != 3) {
        Print.usage()
        return
    }

    val env = Env
    env.name = args[0]
    env.host = args[2]
    env.port = try { args[1].toInt() } catch (e : NumberFormatException) { 0 }
    if (env.port in 0..1024) printError("Port cant't be [0 - 1023]")

    try {
      //  println("Connecting to ${env.host} on port ${env.port}")
        val client = Socket(env.host, env.port)

      //  println("Just connected to " + client.remoteSocketAddress)

        // Out
        val outToServer = client.getOutputStream()
        val out = DataOutputStream(outToServer)

        // In
        val inFromServer = client.getInputStream()
        val `in` = DataInputStream(inFromServer)


        val c : Char
        while (true)
        {
            val a = `in`.read().toChar()
            if (a == '\n') {
                print("\n")
                break
            }
            print(a)
        }

        env.name.forEach { out.writeByte(it.toInt()) }.also { out.writeByte('\n'.toInt()) }
        "voir".forEach { out.writeByte(it.toInt()) }.also { out.writeByte('\n'.toInt()) }

        while (true)
        {
            val a = `in`.read().toChar()
            if (a == '\n') {
                print("\n")
                break
            }
            print(a)
        }
        while (true)
        {
            val a = `in`.read().toChar()
            if (a == '\n') {
                print("\n")
                break
            }
            print(a)
        }

        while (true)
        {
            val a = `in`.read().toChar()
            if (a == '\n') {
                print("\n")
                break
            }
            print(a)
        }
       // out.writeBytes(env.name)
        //out.writeUTF(env.name)
        //println(`in`.readUTF())

       /* out.writeUTF("A data input stream lets an application read primitive Java data types from an underlying input stream in a machine-independent way. An application uses a data output stream to write data that can later be read by a data input stream.")
        out.writeUTF(env.name)
        out.writeUTF("DataInputStream is not necessarily safe for multithreaded access. Thread safety is optional and is the responsibility of users of methods in this class.")
        out.writeUTF(env.name)*/

        client.close()
      /*  println("Trying to connect NAME [${env.name}] to HOST ${env.host} on POSR ${env.port}")
        env.client  = Socket(env.host, env.port)

        println("NAME [${env.name}] is connected to HOST ${env.client.remoteSocketAddress}")
        val out = DataOutputStream(env.client.getOutputStream()!!)

        out.writeUTF("red")
*/
       /* while (true) {
            println("TRUE")
            val inFromServer = env.client.getInputStream()!!
            val `in` = DataInputStream(inFromServer)
            println("Server RESPONSE [${`in`.readUTF()}]")
        }*/
        // println("Server says " + `in`.readChar())
        // env.client.close()
    } catch (e: IOException) { printError(e.message ?: " IOException") } catch (e : Exception) { println("ERROR ** ${e.message}") }
    println("#")
}
