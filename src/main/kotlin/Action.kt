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

	fun advance() {
		Message.sendMessage(ADVANCE)//.also { print(ADVANCE.toUpperCase()) }
	//	if (Message.getMessage() != OK.value) printError(ADVANCE)
	}

	fun turnRight() {
		Message.sendMessage(RIGHT)//.also { print(RIGHT.toUpperCase()) }
	//	if (Message.getMessage() != OK.value) printError(RIGHT)
	}

	fun turnLeft() {
		Message.sendMessage(LEFT)//.also { print(LEFT.toUpperCase()) }
		//if (Message.getMessage() != OK.value) printError(LEFT)
	}

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

	fun inventory(): MutableMap<String, Int> {
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

	fun take(resource: String) : CODE {
		Message.sendMessage("$TAKE $resource\n")
		var msg = Message.getMessage()
		while (msg != OK.value && msg != KO.value)
		{
			println("TAKE $msg")
			msg = Message.getMessage()
		}
		return if (msg == OK.value) OK else KO
		//return if (Message.getMessage().also { if (it != OK.value && it != KO.value) printError(TAKE) } == OK.value) CODE.OK else CODE.KO
	}

	fun put(resource: String) {
		Message.sendMessage("$PUT $resource\n")
	//	return if (Message.getMessage().also { if (it != OK.value && it != KO.value) printError(PUT) } == OK.value) CODE.OK else CODE.KO
	}

	fun kick() {
		Message.sendMessage(KICK)
	//	return if (Message.getMessage().also { if (it != OK.value && it != KO.value) printError(PUT) } == OK.value) CODE.OK else CODE.KO
	}

	/**
	 * return id
	 */
	fun broadcastCalling() : Int {
		val broadcast = "${Env.id}${BROADCASTTYPE.CALLING.ordinal}${Env.level}"
		println("broadcastCalling:$broadcast")
		broadcast(broadcast)

		var message = Message.getMessage()
		println("broadcastCalling message:$message")
		if (message.startsWith(MESSAGE_BROADCAST)) {
			message = message.substring(MESSAGE_BROADCAST.length, message.length)

			val br = messageToBroadcast(message)
			println("origin:${br.origin} id:${br.id} code:${br.code} level:${br.level}")
			if (br.id != Env.id && br.level == Env.level && br.code == BROADCASTTYPE.COMING.ordinal && br.origin == 0) {
				println("THERE:${br.id}")
				return br.id
			}

		}
		return broadcastCalling()
	}

	/**
	 * return origin
	 */
	fun broadcastComing() : Int {
		val broadcast = "${Env.id}${BROADCASTTYPE.COMING.ordinal}${Env.level}"
		println("broadcastComing:$broadcast")
		broadcast(broadcast)
		var message = Message.getMessage()
		if (message.startsWith(MESSAGE_BROADCAST)) {
			message = message.substring(MESSAGE_BROADCAST.length, message.length)

			val br = messageToBroadcast(message)
			println("origin:${br.origin} id:${br.id} code:${br.code} level:${br.level}")
			if (br.id != Env.id && br.level == Env.level && br.code == BROADCASTTYPE.CALLING.ordinal && br.origin == 0) {
				println("THERE:${br.origin}")
				return br.origin
			}
		}
		return broadcastComing()
	}

	private fun broadcast(msg: String) {
		Message.sendMessage(BROADCAST + msg + "\n")
		//val message = Message.getMessage()
		//if (message != OK.value) printError("$BROADCAST message:$message")
	}

	fun incantation() {
		println(INCANTATION)
		Message.sendMessage(INCANTATION)
	}

	fun fork() {
		Message.sendMessage(FORK)
		if (Message.getMessage() != OK.value) printError(FORK)
		//connectPlayer()
	}

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
	}

	fun connectNbr() : Int {
		Message.sendMessage(CONNECT_NBR)
		return try {
			Message.getMessage().toInt()
		} catch (e: NumberFormatException) {
			printError(INVENTORY); 0
		}
	}

}