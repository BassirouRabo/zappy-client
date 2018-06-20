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
import kotlinx.coroutines.experimental.launch
import java.lang.Thread.sleep
import java.util.*
import kotlin.math.E

class Action {

	fun advance() = Message.sendMessage(ADVANCE)

	fun turnRight() = Message.sendMessage(RIGHT)

	fun turnLeft() = Message.sendMessage(LEFT)

	fun see(action: Action): List<List<String>> {
		Message.sendMessage(SEE)

		var msg = ""
		val list: MutableList<List<String>> = mutableListOf()
		val resources = RESOURCE.values().map { it.value }

		while (msg.length < 2 || msg.first() != '{' || msg.last() != '}')
			msg = Message.getMessage(action)
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
			msg = Message.getMessage(action)

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



	fun take(action: Action, resource: String) : CODE {
		Message.sendMessage("$TAKE $resource\n")
		var msg = Message.getMessage(action)
		while (msg != OK.value && msg != KO.value)
		{
			println("TAKE $msg")
			msg = Message.getMessage(action)
		}
		return if (msg == OK.value) OK else KO
	}

	fun put(action: Action, resource: String): CODE {
		Message.sendMessage("$PUT $resource\n")
		var msg = Message.getMessage(action)
		while (msg != OK.value && msg != KO.value)
		{
			println("$PUT $msg")
			msg = Message.getMessage(action)
		}
		return if (msg == OK.value) OK else KO	}

	fun kick() = Message.sendMessage(KICK)

	/**
	 * return id
	 */
	fun broadcastCalling(action: Action) : Int {
		broadcast("${Env.id}${BROADCASTTYPE.CALLING.ordinal}${Env.level}")

		var message = Message.getMessage(action)
		if (message.startsWith(MESSAGE_BROADCAST)) {
			message = message.substring(MESSAGE_BROADCAST.length, message.length)

			val br = messageToBroadcast(message)
			if (br.id != Env.id && br.level == Env.level && br.code == BROADCASTTYPE.COMING.ordinal) {
				println("broadcastCalling : $br")
				if (br.origin == 0)
					broadcast("${Env.id}${BROADCASTTYPE.ARRIVED.ordinal}${Env.level}")
				return br.id
			}

		}
		return broadcastCalling(action)
	}

	/**
	 * return origin
	 */
	fun broadcastComing(action: Action) : Int {
		broadcast("${Env.id}${BROADCASTTYPE.COMING.ordinal}${Env.level}")
		var message = Message.getMessage(action)
		if (message.startsWith(MESSAGE_BROADCAST)) {
			message = message.substring(MESSAGE_BROADCAST.length, message.length)

			val br = messageToBroadcast(message)
			if (br.id != Env.id && br.level == Env.level) {
				println("broadcastComing : $br")
				if (br.code == BROADCASTTYPE.CALLING.ordinal)
					return br.origin
				if (br.code == BROADCASTTYPE.ARRIVED.ordinal && br.origin == 0)
					return -1
			}
		}
		return broadcastComing(action)
	}

	private fun broadcast(msg: String) = Message.sendMessage(BROADCAST + msg + "\n")

	fun incantation() {
		Message.sendMessage(INCANTATION)
	}

	fun fork(action: Action) {
		Message.sendMessage(FORK)
		if (Message.getMessage(action) != OK.value) printError(FORK)
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

	fun connectNbr(action: Action) : Int {
		Message.sendMessage(CONNECT_NBR)
		return try {
			Message.getMessage(action).toInt()
		} catch (e: NumberFormatException) {
			printError(INVENTORY); 0
		}
	}

}