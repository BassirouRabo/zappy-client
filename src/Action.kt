import kotlin.system.exitProcess
import CODE.*
import Message.getMessage
import Print.printError

class Action {
    private val ok = "ok"
    private val ko = "ko"

    fun advance() {
        Message.sendMessage(CMD.ADVANCE)
        if (Message.getMessage() != ok) printError(CMD.ADVANCE)
    }

    fun turnRight() {
        Message.sendMessage(CMD.RIGHT)
        if (Message.getMessage() != ok) printError(CMD.RIGHT)
    }

    fun turnLeft() {
        Message.sendMessage(CMD.LEFT)
        if (Message.getMessage() != ok) printError(CMD.LEFT)
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
        Message.sendMessage("${CMD.TAKE} $resource\n")
        return if (Message.getMessage().also { println(it) }.also { if(it != ok && it != ko) printError(CMD.TAKE) } == ok) CODE.OK else CODE.KO
    }

    fun put(resource: String) : CODE {
        Message.sendMessage("${CMD.PUT} $resource\n")
        return if (Message.getMessage().also { println(it) }.also { if(it != ok && it != ko) printError(CMD.PUT) } == ok) CODE.OK else CODE.KO
    }

    fun kick() : CODE {
        Message.sendMessage(CMD.KICK)
        return if (Message.getMessage().also { println(it) }.also { if(it != ok && it != ko) printError(CMD.PUT) } == ok) CODE.OK else CODE.KO
    }

    fun broadcast(msg: String) {
        Message.sendMessage(CMD.BROADCAST + msg + "\n")
        if (Message.getMessage() != ok) printError(CMD.LEFT)
    }

    fun incantation(): Int {
        Message.sendMessage(CMD.INCANTATION)
        return try { Message.getMessage().toInt() } catch (e : NumberFormatException) { printError(CMD.INVENTORY) ; 0 }
    }

    fun fork() {
        Message.sendMessage(CMD.FORK)
        if (Message.getMessage()!= ok) printError(CMD.FORK)
    }

    fun connectNbr() : Int {
        Message.sendMessage(CMD.CONNECT_NBR)
        return try { Message.getMessage().toInt() } catch (e : NumberFormatException) { printError(CMD.INVENTORY) ; 0 }
    }

}