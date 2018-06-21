import CODE.OK
import Resource.RESOURCE
import kotlinx.coroutines.experimental.launch
import java.lang.Thread.sleep

class State {

	private val levels: Array<Map<String, Int>> = arrayOf(
		mapOf("linemate" to 1, "deraumere" to 0, "sibur" to 0, "mendiane" to 0, "phiras" to 0, "thystame" to 0),
		mapOf("linemate" to 1, "deraumere" to 1, "sibur" to 1, "mendiane" to 0, "phiras" to 0, "thystame" to 0),
		mapOf("linemate" to 2, "deraumere" to 0, "sibur" to 1, "mendiane" to 0, "phiras" to 2, "thystame" to 0),
		mapOf("linemate" to 1, "deraumere" to 1, "sibur" to 2, "mendiane" to 0, "phiras" to 1, "thystame" to 0),
		mapOf("linemate" to 1, "deraumere" to 2, "sibur" to 1, "mendiane" to 3, "phiras" to 0, "thystame" to 0),
		mapOf("linemate" to 1, "deraumere" to 2, "sibur" to 3, "mendiane" to 0, "phiras" to 1, "thystame" to 0),
		mapOf("linemate" to 2, "deraumere" to 2, "sibur" to 2, "mendiane" to 2, "phiras" to 2, "thystame" to 1)
	)

	private val players = arrayOf(1, 2, 2, 4, 4, 6, 6)

	fun walk(action: Action) {
		var floor = 0
		var i = 0
		val inventory = action.inventory(action)
		val see = action.see(action)
		if (action.connectNbr(action) > 0) action.fork(action)

		while (i < see.size) {

			doCollecte(see[i], inventory, action)
			if (canIncantate(action, inventory)) break

			collectRight(i, floor, see, inventory, action)
			if (canIncantate(action, inventory)) break

			collectLeft(i, floor, see, inventory, action)
			if (canIncantate(action, inventory)) break

			i = ++floor * (floor + 1)
			action.advance()
		}
	}

	private fun canIncantate(action: Action, inventory: MutableMap<String, Int>): Boolean {
		println("canIncantate")
		if (checkBroadcast(action))
			return goBroadcast(action)
		else if (checkInventory(action, inventory))
		{
			val res = 	doBroadcast(action)
			println("####")
			return res
		}
		return false
	}

	private fun checkInventory(action: Action, inventory: MutableMap<String, Int>): Boolean {
		for ((res, value) in levels[Env.level - 1])
			if (inventory.containsKey(res) && inventory[res]!! < value) {
				println("checkInventory false")
				return false
			}
		println("checkInventory true")
		return true
	}

	private fun checkBroadcast(action: Action): Boolean {
		val c = Env.broadcastCallingReceive
		println("checkBroadcast $c")
		return c
	}

	private fun doBroadcast(action: Action): Boolean {
		println("doBroadcast Env.broadcastCallingReceive: ${ Env.broadcastCallingReceive}")
		levels[Env.level - 1].forEach { res, nbr ->
			var n = nbr
			while (n-- > 0)
				action.put(action, res)
		}
		if (checkBroadcast(action)) {
			goBroadcast(action)
			return true
		}
		println("doBroadcast")
		val playersOnSpot = mutableSetOf<Int>()
		playersOnSpot.add(Env.id)

		while (playersOnSpot.size < players[Env.level - 1])
		{
			println("playersOnSpot.size ${playersOnSpot.size}")
			playersOnSpot.add(action.broadcastCalling(action))
		}
		action.incantation()
		Env.broadcastCallingReceive = false
		println("doBroadcast END")
		return true
	}

	private fun goBroadcast(action: Action): Boolean {
		println("goBroadcast")
		while (Env.canMove) {
			when (action.broadcastComing(action)) {
				0, -1 -> {
					Env.canMove = false
				}
				1 -> {
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
				}
				2 -> {
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
					action.turnLeft()
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
				}
				3 -> {
					action.turnLeft()
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
				}
				4 -> {
					action.turnLeft()
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
					action.turnLeft()
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
				}
				5 -> {
					action.turnLeft()
					action.turnLeft()
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
				}
				6 -> {
					action.turnRight()
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
					action.turnRight()
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
				}
				7 -> {
					action.turnRight()
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
				}
				8 -> {
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
					action.turnRight()
					action.advance()
					action.take(action, Resource.RESOURCE.FOOD.value)
				}
			}
		}
		while (!Env.canMove)
			continue
		Env.broadcastCallingReceive = false
		return true
	}

	private fun doCollecte(resources: List<String>, inventory: MutableMap<String, Int>, action: Action) {
		resources.forEach {
			if (Resource.getMaxStones(RESOURCE.valueOf(it.toUpperCase())) > inventory[it]!!) {
				if (action.take(action, it) == OK) inventory[it] = inventory[it]!! + 1
			}
		}
	}

	private fun collectRight(_indice: Int, _floor: Int, see: List<List<String>>, inventory: MutableMap<String, Int>, action: Action) {
		var indice = _indice
		var floor = _floor

		action.turnRight()
		while (floor-- > 0) {
			action.advance()
			doCollecte(see[++indice], inventory, action)
		}
		action.turnLeft()
		action.turnLeft()
		floor = _floor
		while (floor-- > 0) action.advance()
		action.turnRight()
	}

	private fun collectLeft(_indice: Int, _floor: Int, see: List<List<String>>, inventory: MutableMap<String, Int>, action: Action) {
		var indice = _indice
		var floor = _floor

		action.turnLeft()
		while (floor-- > 0) {
			action.advance()
			doCollecte(see[--indice], inventory, action)
		}
		action.turnRight()
		action.turnRight()
		floor = _floor
		while (floor-- > 0) action.advance()
		action.turnLeft()
	}

}