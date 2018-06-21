import CODE.OK
import Resource.RESOURCE

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
		val see = action.see()
		if (action.connectNbr(action) > 0) action.fork(action)

		while (i < see.size) {
			if (!canCollect(see[i], inventory, action)
				|| canDoBroadcast(action, inventory)

				|| !canCollectRight(i, floor, see, inventory, action)
				|| canDoBroadcast(action, inventory)

				|| !canCollectLeft(i, floor, see, inventory, action)
				|| canDoBroadcast(action, inventory))
				break

			i = ++floor * (floor + 1)
			action.advance()
		}
	}

	private fun canDoBroadcast(action: Action, inventory: MutableMap<String, Int>): Boolean {
		for ((res, value) in levels[Env.level - 1])
			if (inventory.containsKey(res) && inventory[res]!! < value)
				return false
		doBroadcast(action)
		return true
	}

	private fun doBroadcast(action: Action) {
		println("doBroadcast")
		levels[Env.level - 1].forEach { res, nbr ->
			var n = nbr
			while (n-- > 0) {
				if (Env.hasBeenCalled[Env.level] != -1) {
					goBroadcast(action)
					break
				}
				action.put(res)
			}
		}

		if (Env.hasBeenCalled[Env.level] != -1) {
			goBroadcast(action)
			return
		}

		val playersOnSpot = mutableSetOf<Int>()
		playersOnSpot.add(Env.id)

		while (playersOnSpot.size < players[Env.level - 1])
		{
			println("playersOnSpot.size ${playersOnSpot.size}")
			playersOnSpot.add(action.broadcastCalling(action))
		}
		println("incantation START")
		action.incantation()
		println("incantation END")
	}

	private fun goBroadcast(action: Action) {
		println("goBroadcast")
		when (Env.hasBeenCalled[Env.level]) {
			0 -> {
				while (Env.hasBeenCalled[Env.level] != -1)
				;
			}
			1 -> {
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
			}
			2 -> {
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
				action.turnLeft()
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
			}
			3 -> {
				action.turnLeft()
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
			}
			4 -> {
				action.turnLeft()
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
				action.turnLeft()
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
			}
			5 -> {
				action.turnLeft()
				action.turnLeft()
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
			}
			6 -> {
				action.turnRight()
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
				action.turnRight()
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
			}
			7 -> {
				action.turnRight()
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
			}
			8 -> {
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
				action.turnRight()
				action.advance()
				action.take(Resource.RESOURCE.FOOD.value)
			}
		}
		action.broadcastComing()
	}

	private fun canCollect(resources: List<String>, inventory: MutableMap<String, Int>, action: Action): Boolean {
		println("canCollect")
		resources.forEach {
			if (Env.hasBeenCalled[Env.level] != -1) {
				goBroadcast(action)
				return false
			}
			if (Resource.getMaxStones(RESOURCE.valueOf(it.toUpperCase())) > inventory[it]!!) {
				if (action.take(it) == OK)
					inventory[it] = inventory[it]!! + 1
			}
		}
		return true
	}

	private fun canCollectRight(_indice: Int, _floor: Int, see: List<List<String>>, inventory: MutableMap<String, Int>, action: Action): Boolean {
		println("canCollectRight")
		var indice = _indice
		var floor = _floor

		action.turnRight()
		while (floor-- > 0) {
			action.advance()
			if (!canCollect(see[++indice], inventory, action))
				return false
		}
		action.turnLeft()
		action.turnLeft()
		floor = _floor
		while (floor-- > 0)
			action.advance()
		action.turnRight()
		return true
	}

	private fun canCollectLeft(_indice: Int, _floor: Int, see: List<List<String>>, inventory: MutableMap<String, Int>, action: Action): Boolean {
		println("canCollectLeft")
		var indice = _indice
		var floor = _floor

		action.turnLeft()
		while (floor-- > 0) {
			action.advance()
			if (!canCollect(see[--indice], inventory, action))
				return false
		}
		action.turnRight()
		action.turnRight()
		floor = _floor
		while (floor-- > 0) action.advance()
		action.turnLeft()
		return true
	}

}