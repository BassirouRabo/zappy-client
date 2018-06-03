import kotlin.system.exitProcess
import CODE.*
import Message.getMessage
import Print.printError

class Action {

    companion object {
        private val DEATH = "DEATH"
        private val INCANTATION = "elevation in progress current level : "
        private val ok = "ok"
        private val ko = "ko"

        private object CMD {
            const val ADVANCE: String = "avance\n"     //advance
            const val RIGHT: String = "droite\n"        // right
            const val LEFT: String = "gauche\n"         // left
            const val SEE: String = "voir\n"    // see
            const val INVENTORY: String = "inventaire\n"    // inventory
            const val TAKE: String = "prend"                // take
            const val PUT: String = "pose"                  // put
            const val KICK: String = "expulse\n"        // kick
            const val BROADCAST: String = "broadcast "
            const val INCANTATION: String = "incantation\n"
            const val FORK: String = "fork\n"
            const val CONNECT_NBR: String = "connect_nbr\n"
        }

        private fun parse(Env : Env, msg: String) : CODE {
            var code = KO
            if (msg == DEATH) {
                code = OK
                println(DEATH)
                exitProcess(0)
            } else if (msg.startsWith(INCANTATION, false)) {
                code = OK
                try {
                    Env.level = msg.substring(INCANTATION.length, msg.length).toInt()
                } catch (e : NumberFormatException) { printError(INCANTATION) }
            }
            return code
        }


        private fun getResource(name: String): Resource {
            if (name === "  ") println("null")
            println("[  $name${name.length}]")
            val stones = Stone.getStones()
            return when {
                stones.contains(name) -> return Resource.values()[stones.indexOf(name)]
                name == "food" -> return Resource.FOOD
                else -> {
                    printError(name + " - " +CMD.SEE)
                    Resource.FOOD
                }
            }
        }



        fun getMessageNbr(msg: String) : Int {
            var nbr = 0
            try {
                nbr = msg.toInt()
            } catch (e : NumberFormatException) {printError(CMD.CONNECT_NBR)}
            return nbr
        }
    }

    fun advance() {
        Message.sendMessage(CMD.ADVANCE)
        if (!getMessage().equals(ok)) printError(CMD.ADVANCE)
    }

    fun turnRight() {
        Message.sendMessage(CMD.RIGHT)
        if (!getMessage().equals(ok)) printError(CMD.RIGHT)
    }

    fun turnLeft() {
        Message.sendMessage(CMD.LEFT)
        if (!getMessage().equals(ok)) printError(CMD.LEFT)
    }

    // {food food linemate linemate linemate linemate deraumere deraumere deraumere deraumere mendiane phiras phiras phiras phiras thystame thystame, food food food food food food food linemate linemate linemate linemate sibur sibur sibur sibur sibur sibur sibur sibur mendiane mendiane mendiane mendiane phiras phiras phiras phiras phiras phiras phiras thystame, linemate linemate linemate linemate deraumere deraumere deraumere sibur sibur sibur sibur sibur sibur sibur mendiane mendiane mendiane mendiane phiras phiras phiras phiras phiras thystame thystame thystame}

    fun see() : List<List<Resource>> {
        Message.sendMessage(CMD.SEE)

        val msg = Message.getMessage().also { println(it) }
        val list : MutableList<List<Resource>> = mutableListOf()

        if (msg.length < 2 && (msg.first() != '{' || msg.last() != '}')) printError(CMD.INCANTATION)

        msg.substring(1, msg.length - 1).split(",").map { it.trim() }.forEach {
            list.add((it.split(" ").map { it.trim()}.map { getResource(it) }))
        }
        return list
    }

    fun inventory() : Inventory {
        Message.sendMessage(CMD.INVENTORY)
        val inventory = Inventory()
        var name : String = ""
        var value : Int = 0
        var msg = getMessage()
        if (msg.length < 4 && (msg.first() != '{' || msg.last() != '}')) printError(CMD.INCANTATION)

        msg = msg.substring(1, msg.length - 1)

        for (c in msg) {
            if (c in 'a'..'z') name.plus(c)
            else if (c in '0'..'9') (value * 10) + (c - '0')
            else if (c.equals(',')) {
                try { inventory.javaClass.getDeclaredField(name).also { it.set(inventory, value) } } catch (e: NoSuchFieldException) { printError(CMD.INVENTORY)}
                name = ""
                value = 0
            }
        }
        return inventory
    }

    fun take(resource: String) : CODE {
        Message.sendMessage(CMD.TAKE + resource)
        val msg = getMessage()
        if (msg.equals(ok)) return CODE.OK
        else if (msg.equals(ko)) return CODE.KO
        return CODE.KO
    }

    fun put(resource: String) : CODE {
        Message.sendMessage(CMD.PUT + resource)
        val msg = getMessage()
        if (msg.equals(ok)) return CODE.OK
        else if (msg.equals(ko)) return CODE.KO
        return CODE.KO
    }

    fun kick() : CODE {
        Message.sendMessage(CMD.KICK)
        val msg = getMessage()
        if (msg.equals(ok)) return CODE.OK
        else if (msg.equals(ko)) return CODE.KO
        return CODE.KO
    }

    fun broadcast(msg: String) {
        Message.sendMessage(CMD.BROADCAST + msg)
    }

    fun incantation(): Int {
        Message.sendMessage(CMD.INCANTATION)
        return getMessageNbr(getMessage())
    }

    fun fork() {
        Message.sendMessage(CMD.FORK)
        if (!getMessage().equals(ok)) printError(CMD.FORK)
    }

    fun connectNbr() : Int {
        Message.sendMessage(CMD.CONNECT_NBR)
        return getMessageNbr(getMessage())
    }

}