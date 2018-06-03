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
        if (getMessage() != ok) printError(CMD.LEFT)
    }

    fun see() : List<List<Resource.RES>> {
        Message.sendMessage(CMD.SEE)

        val msg = Message.getMessage()
        val list : MutableList<List<Resource.RES>> = mutableListOf()

        if (msg.length < 2 || msg.first() != '{' || msg.last() != '}') printError(CMD.INCANTATION)

        msg.substring(1, msg.length - 1).split(",").map { it.trim() }.forEach { list.add((it.split(" ").map { it.trim()}.filter { (Resource.getStones().contains(it) || it == "food") }.map { when { Resource.getStones().contains(it) -> Resource.RES.values()[Resource.getStones().indexOf(it)] else -> Resource.RES.FOOD } })) }
        return list
    }

    fun inventory() : Map<String, Int> {
        Message.sendMessage(CMD.INVENTORY)

        val msg = Message.getMessage()
        val inventory = Resource.getStonesMap()

        if (msg.length < 2 || msg.first() != '{' || msg.last() != '}') printError(CMD.INVENTORY)

        msg.substring(1, msg.length - 1).split(",").map { it.trim() }.forEach {
            it.split(" ").map { it.trim() }.also {
                if (it.size == 2 && inventory.containsKey(it[0]))
                    inventory[it[0]] = try { it[1].toInt() }  catch (e : NumberFormatException) { printError(CMD.INVENTORY) ; 0 }
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