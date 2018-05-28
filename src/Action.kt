import java.io.DataInputStream
import java.io.IOException
import kotlin.system.exitProcess
import CODE.*
import Print.printError
import java.io.DataOutputStream

class Action(val env : Env) {

    companion object {
        private val DEATH = "DEATH"
        private val INCANTATION = "elevation in progress current level : "
        private val ok = "ok"
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



        private fun getResourceCode(name: String): Resource {
            val stones = arrayOf("food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame")
            if (stones.contains(name)) return Resource.values()[stones.indexOf(name)] else { printError(CMD.see) }
            return Resource.ERROR
        }

        fun getMessage(env: Env) : String {
            val msg: String = ""
            do {
                try {
                    val input = DataInputStream(env.client.getInputStream()!!)
                    while (true) {
                        val c = input.readChar()
                        if (c == '\n') break else msg.plus(c)
                    }
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
            } catch (e: IOException) { println(e.message) }
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

    fun see() : List<List<Resource>> {
        sendMessage(env, CMD.see)

        val list : MutableList<MutableList<Resource>> = mutableListOf()
        val resources : MutableList<Resource> = mutableListOf()
        var name : String = ""
        var i  = 0

        var msg = getMessage(env)

        if (msg.length < 2 && (msg.first() != '{' || msg.last() != '}')) printError(CMD.incantation)
        msg = msg.substring(1, msg.length - 1)

        for (c in msg) {
            if (c in 'a'..'z') name.plus(c)
            else if (c == ' ') {
                resources.add(getResourceCode(name))
                name = ""
            } else if (c == ',' && !name.equals("")) {
                list.add(resources)
                resources.clear()
            }
        }
        return list
    }

    fun inventory() : Inventory {
        sendMessage(env, CMD.inventory)
        val inventory = Inventory()
        var name : String = ""
        var value : Int = 0
        var msg = getMessage(env)
        if (msg.length < 4 && (msg.first() != '{' || msg.last() != '}')) printError(CMD.incantation)

        msg = msg.substring(1, msg.length - 1)

        for (c in msg) {
            if (c in 'a'..'z') name.plus(c)
            else if (c in '0'..'9') (value * 10) + (c - '0')
            else if (c.equals(',')) {
                try { inventory.javaClass.getDeclaredField(name).also { it.set(inventory, value) } } catch (e: NoSuchFieldException) { printError(CMD.inventory)}
                name = ""
                value = 0
            }
        }
        return inventory
    }

    fun take(resource: String) : CODE {
        sendMessage(env, CMD.take + resource)
        val msg = getMessage(env)
        if (msg.equals(ok)) return CODE.OK
        else if (msg.equals(ko)) return CODE.KO
        return CODE.KO
    }

    fun put(resource: String) : CODE {
        sendMessage(env, CMD.put + resource)
        val msg = getMessage(env)
        if (msg.equals(ok)) return CODE.OK
        else if (msg.equals(ko)) return CODE.KO
        return CODE.KO
    }

    fun kict() : CODE {
        sendMessage(env, CMD.kick)
        val msg = getMessage(env)
        if (msg.equals(ok)) return CODE.OK
        else if (msg.equals(ko)) return CODE.KO
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