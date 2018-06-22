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

	fun advance(env: Env) = Message.sendMessage(env, ADVANCE)

	fun turnRight(env: Env) = Message.sendMessage(env, RIGHT)

	fun turnLeft(env: Env) = Message.sendMessage(env, LEFT)

	fun see(env: Env): List<List<String>> {
		Message.sendMessage(env, SEE)

		var msg = ""
		val list: MutableList<List<String>> = mutableListOf()
		val resources = RESOURCE.values().map { it.value }

		while (msg.length < 2 || msg.first() != '{' || msg.last() != '}')
			msg = Message.getMessage(env)
		if (msg.length < 2 || msg.first() != '{' || msg.last() != '}') printError(INCANTATION)

		msg.substring(1, msg.length - 1)
			.split(",")
			.map { it.trim() }
			.forEach {
				list.add((it.split(" ").filter { resources.contains(it.trim()) })) }
		return list.toMutableList()
	}

	fun inventory(env: Env, action: Action): MutableMap<String, Int> {
		Message.sendMessage(env, INVENTORY)
		var msg = ""
		val inventory = getStonesMap()

		while (msg.length < 2 || msg.first() != '{' || msg.last() != '}')
			msg = Message.getMessage(env)
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

	fun take(env: Env, resource: String): CODE {
		Message.sendMessage(env, "$TAKE $resource\n")
		var msg = Message.getMessage(env)
		while (msg != OK.value && msg != KO.value)
			msg = Message.getMessage(env)
		return if (msg == OK.value) OK else KO
	}

	fun put(env: Env, resource: String): CODE {
		Message.sendMessage(env, "$PUT $resource\n")
		var msg = Message.getMessage(env)
		while (msg != OK.value && msg != KO.value)
			msg = Message.getMessage(env)
		return if (msg == OK.value) OK else KO
	}

	fun kick(env: Env) = Message.sendMessage(env, KICK)

	/**
	 * return id
	 */
	fun broadcastCalling(env: Env): Int {
		val broadcastMessageSend = "${env.id}${BROADCASTTYPE.CALLING.ordinal}${env.level}"
		broadcast(env, broadcastMessageSend)
		while (true) {
			val br: Broadcast = Message.getMessageComing(env, broadcastMessageSend)
			if (br.origin == 0)
				return br.id
		}
	}

	/**
	 * return origin
	 */
	fun broadcastComing(env: Env) {
		val broadcast = "${env.id}${BROADCASTTYPE.COMING.ordinal}${env.level}"
		broadcast(env, broadcast)
	}

	fun broadcast(env: Env, msg: String) {
		Message.sendMessage(env, BROADCAST + msg + "\n")
	}

	fun incantation(env: Env) {
		Message.sendMessage(env, INCANTATION)
	}

	fun fork(env: Env): CODE {
		Message.sendMessage(env, FORK)
		var msg = Message.getMessage(env)
		while (msg != OK.value && msg != KO.value)
			msg = Message.getMessage(env)
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

	fun connectNbr(env: Env): Int {
		Message.sendMessage(env, CONNECT_NBR)
		while (true) {
			val msg = Message.getMessage(env)
			try {
				return msg.toInt()
			} catch (e: NumberFormatException) {
			}
		}
	}

}