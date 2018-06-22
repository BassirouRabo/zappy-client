import CMD.ADVANCE
import CMD.BROADCAST
import CMD.CONNECT_NBR
import CMD.FORK
import CMD.INCANTATION
import CMD.INVENTORY
import CMD.KICK
import CMD.LEFT
import CMD.PUT
import CMD.RIGHT
import CMD.SEE
import CMD.TAKE
import CODE.KO
import CODE.OK
import Print.printError
import Resource.RESOURCE
import Resource.getStonesMap

class Action {

	fun advance() = Message.sendMessage(ADVANCE)

	fun turnRight() = Message.sendMessage(RIGHT)

	fun turnLeft() = Message.sendMessage(LEFT)

	fun see(): List<List<String>> {
		Message.sendMessage(SEE)

		var msg = ""
		val list: MutableList<List<String>> = mutableListOf()
		val resources = RESOURCE.values().map { it.value }

		while (msg.length < 2 || msg.first() != '{' || msg.last() != '}')
			msg = Message.getMessage()
		if (msg.length < 2 || msg.first() != '{' || msg.last() != '}') printError(INCANTATION)

		msg.substring(1, msg.length - 1)
			.split(",")
			.map { it.trim() }
			.forEach {
				list.add((it.split(" ").filter { resources.contains(it.trim()) })) }
		return list.toMutableList()
	}

	fun inventory(action: Action): MutableMap<String, Int> {
		Message.sendMessage(INVENTORY)
		var msg = ""
		val inventory = getStonesMap()

		while (msg.length < 2 || msg.first() != '{' || msg.last() != '}')
			msg = Message.getMessage()
		msg
			.substring(1, msg.length - 1)
			.split(",")
			.map { it.trim() }
			.forEach {
				it.split(" ").map { it.trim() }.also {
					if (it.size == 2 && inventory.containsKey(it[0]))
						inventory[it[0]] = try {
							it[1].toInt()
						} catch (e: NumberFormatException) {
							printError("# $INVENTORY"); 0
						}
				}
			}

		return inventory
	}

	fun take(resource: String): CODE {
		Message.sendMessage("$TAKE $resource\n")
		var msg = Message.getMessage()
		while (msg != OK.value && msg != KO.value)
			msg = Message.getMessage()
		return if (msg == OK.value) OK else KO
	}

	fun put(resource: String): CODE {
		Message.sendMessage("$PUT $resource\n")
		var msg = Message.getMessage()
		while (msg != OK.value && msg != KO.value)
			msg = Message.getMessage()
		return if (msg == OK.value) OK else KO
	}

	fun kick() = Message.sendMessage(KICK)

	/**
	 * return id
	 */
	fun broadcastCalling(): Int {
		val broadcastMessageSend = "${Env.id}${BROADCASTTYPE.CALLING.ordinal}${Env.level}"
		broadcast(broadcastMessageSend)
		while (true) {
			val br: Broadcast = Message.getMessageComing(broadcastMessageSend)
			if (br.origin == 0)
				return br.id
		}
	}

	/**
	 * return origin
	 */
	fun broadcastComing() {
		val broadcast = "${Env.id}${BROADCASTTYPE.COMING.ordinal}${Env.level}"
		broadcast(broadcast)
	}

	fun broadcast(msg: String) {
		Message.sendMessage(BROADCAST + msg + "\n")
	}

	fun incantation() {
		Message.sendMessage(INCANTATION)
	}

	fun fork(): CODE {
		Message.sendMessage(FORK)
		var msg = Message.getMessage()
		while (msg != OK.value && msg != KO.value)
			msg = Message.getMessage()
		return if (msg == OK.value) OK else KO
	}
/*
	private fun connectPlayer() {
		if (connectNbr() > 0) {
			launch {
				sleep(5000)
				val code = Random().nextInt()
				try {
					val proc = ProcessBuilder("java", "-jar", "../../../build/libs/client-1.0.jar", "red", "4242", "localhost").start()
					Scanner(proc.inputStream).use {
						while (it.hasNextLine()) println("$code: " + it.nextLine())
					}
				}catch (e: Exception) {
					println("ERR ${e.message}")}
			}
			//	println("NEW PLAYER")
		}
	}*/

	fun connectNbr(): Int {
		Message.sendMessage(CONNECT_NBR)
		while (true) {
			val msg = Message.getMessage()
			try {
				return msg.toInt()
			} catch (e: NumberFormatException) {
			}
		}
	}

}