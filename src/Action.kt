import java.io.DataInputStream
import java.io.IOException
import kotlin.system.exitProcess
import CODE.*
import java.io.DataOutputStream

class Action(val env : Env) {

    companion object {
        private val DEATH = "DEATH"
        private val INCANTATION = "elevation in progress current level : "
        private val ok = "ko"
        private val ko = "ko"

        private object CMD {
            val advance: String = "advamce"
            val right: String = "right"
            var left: String = "left"
            val see: String = "see"
            val inventory: String = "inventory"
            val take: String = "take "
            val put: String = "put "
            val kick: String = "kick"
            val broadcast: String = "broadcast "
            val incantation: String = "incantation"
            val fork: String = "fork"
            val connect_nbr: String = "connect_nbr"
        }

        private fun parse(env : Env, msg: String) : CODE {
            var code = KO
            if (msg.equals(DEATH)) {
                code = OK
                println(DEATH)
                exitProcess(0)
            } else if (msg.startsWith(INCANTATION, false)) {
                code = OK
                try {
                    env.level = msg.substring(INCANTATION.length, msg.length).toInt()
                } catch (e : NumberFormatException) { printError(INCANTATION) }
            }
            return code
        }

        private fun printError(msg: String) {
            println("ERROR MESSAGE FOR COMMAND $msg")
            exitProcess(-1)
        }

        fun getMessage(env: Env) : String {
            var msg: String
            do {
                try {
                    msg = DataInputStream(env.client.getInputStream()!!).readUTF()
                } catch (e: IOException) {
                    println("ERROR ${e.message}")
                    exitProcess(-1)
                }
            } while (parse(env, msg) == OK)
            return msg
        }

        fun sendMessage(env: Env, msg: String) {
            try {
                val outToServer = env.client.getOutputStream()!!
                val out = DataOutputStream(outToServer)

                out.writeUTF(msg);
            } catch (e: IOException) {
                println("ERROR ${e.message}")
                exitProcess(-1)
            }
        }

        fun getMessageNbr(msg: String) : Int {
            var nbr = 0
            try {
                nbr = msg.toInt()
            } catch (e : NumberFormatException) {printError(CMD.connect_nbr)}
            return nbr
        }
    }

    fun advance() {
        sendMessage(env, CMD.advance)
        if (!getMessage(env).equals(ok)) printError(CMD.advance)
    }

    fun turnRight() {
        sendMessage(env, CMD.right)
        if (!getMessage(env).equals(ok)) printError(CMD.right)
    }

    fun turnLeft() {
        sendMessage(env, CMD.left)
        if (!getMessage(env).equals(ok)) printError(CMD.left)
    }

    fun see() : List<String> {
        sendMessage(env, CMD.see)
        return listOf()
    }

    fun inventory() : List<String> {
        sendMessage(env, CMD.inventory)
        return listOf()
    }

    fun take(resource: String) : CODE {
        sendMessage(env, CMD.take + resource)
        val msg = getMessage(env)
        if (msg.equals(ok)) return CODE.OK
        else if (msg.equals(ok)) return CODE.KO
        return CODE.KO
    }

    fun put(resource: String) : CODE {
        sendMessage(env, CMD.put + resource)
        val msg = getMessage(env)
        if (msg.equals(ok)) return CODE.OK
        else if (msg.equals(ok)) return CODE.KO
        return CODE.KO
    }

    fun kict() : CODE {
        sendMessage(env, CMD.kick)
        val msg = getMessage(env)
        if (msg.equals(ok)) return CODE.OK
        else if (msg.equals(ok)) return CODE.KO
        return CODE.KO
    }

    fun broadcast(msg: String) {
        sendMessage(env, CMD.broadcast + msg)
    }

    fun incantation(): Int {
        sendMessage(env, CMD.incantation)
        return getMessageNbr(getMessage(env))
    }

    fun fork() {
        sendMessage(env, CMD.fork)
        if (!getMessage(env).equals(ok)) printError(CMD.fork)
    }

    fun connectNbr() : Int {
        sendMessage(env, CMD.connect_nbr)
        return getMessageNbr(getMessage(env))
    }
}