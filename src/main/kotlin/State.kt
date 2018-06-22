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

	fun walk(env: Env, action: Action) {
		println("walk")
		action.fork(env)
		var floor = 0
		var i = 0
		val inventory = action.inventory(env, action)
		val see = action.see(env)
		if (action.connectNbr(env) > 0) action.fork(env)
		while (i < see.size) {
			if (!canCollect(env, see[i], inventory, action)
				|| canDoBroadcast(env, action, inventory)

				|| !canCollectRight(env, i, floor, see, inventory, action)
				|| canDoBroadcast(env, action, inventory)

				|| !canCollectLeft(env, i, floor, see, inventory, action)
				|| canDoBroadcast(env, action, inventory))
				break
			i = ++floor * (floor + 1)
			action.advance(env)
		}
	}

	private fun canDoBroadcast(env: Env, action: Action, inventory: MutableMap<String, Int>): Boolean {
		for ((res, value) in levels[env.level - 1])
			if (inventory.containsKey(res) && inventory[res]!! < value)
				return false
		doBroadcast(env, action)
		return true
	}

	private fun doBroadcast(env: Env, action: Action) {
		levels[env.level - 1].forEach { res, nbr ->
			var n = nbr
			while (n-- > 0) {
				if (env.hasBeenCalled[env.level] != -1) {
					goBroadcast(env, action)
					break
				}
				action.put(env, res)
			}
		}

		if (env.hasBeenCalled[env.level] != -1) {
			goBroadcast(env, action)
		} else {
			val playersOnSpot = mutableSetOf<Int>()
			playersOnSpot.add(env.id)

			while (playersOnSpot.size < players[env.level - 1]) {
				println("playersOnSpot.size ${playersOnSpot.size}")
				playersOnSpot.add(action.broadcastCalling(env))
			}
			action.incantation(env)
		}
	}

	private fun goBroadcast(env: Env, action: Action) {
		println("goBroadcast Env.hasBeenCalled[Env.level] ${env.hasBeenCalled[env.level]}")
		when (env.hasBeenCalled[env.level]) {
			0 -> {
				while (env.hasBeenCalled[env.level] != -1) {
					println("* Env.hasBeenCalled[Env.level] ${env.hasBeenCalled[env.level]}")
					try {
						Thread.sleep(2000)
					} catch (e: Exception) {
						println("THREAD EX ${e.message}")
					}
				}
			}
			1 -> {
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
			}
			2 -> {
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
				action.turnLeft(env)
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
			}
			3 -> {
				action.turnLeft(env)
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
			}
			4 -> {
				action.turnLeft(env)
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
				action.turnLeft(env)
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
			}
			5 -> {
				action.turnLeft(env)
				action.turnLeft(env)
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
			}
			6 -> {
				action.turnRight(env)
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
				action.turnRight(env)
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
			}
			7 -> {
				action.turnRight(env)
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
			}
			8 -> {
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
				action.turnRight(env)
				action.advance(env)
				action.take(env, Resource.RESOURCE.FOOD.value)
			}
		}
		action.broadcastComing(env)
	}

	private fun canCollect(env: Env, resources: List<String>, inventory: MutableMap<String, Int>, action: Action): Boolean {
		if (env.hasBeenCalled[env.level] != -1) {
			goBroadcast(env, action)
			return false
		}
		println("canCollect ${action.see(env)[0]} - resource: $resources - Env.level ${env.level} - Env.hasBeenCalled[Env.level] ${env.hasBeenCalled[env.level]}")
		resources.forEach {
			if (env.hasBeenCalled[env.level] != -1) {
				goBroadcast(env, action)
				return false
			}
			if (Resource.getMaxStones(env, RESOURCE.valueOf(it.toUpperCase())) > inventory[it]!!) {
				if (action.take(env, it) == OK)
					inventory[it] = inventory[it]!! + 1
			}
		}
		return true
	}

	private fun canCollectRight(env: Env, _indice: Int, _floor: Int, see: List<List<String>>, inventory: MutableMap<String, Int>, action: Action): Boolean {
		var indice = _indice
		var floor = _floor

		action.turnRight(env)
		while (floor-- > 0) {
			action.advance(env)
			if (!canCollect(env, see[++indice], inventory, action))
				return false
		}
		action.turnLeft(env)
		action.turnLeft(env)
		floor = _floor
		while (floor-- > 0)
			action.advance(env)
		action.turnRight(env)
		return true
	}

	private fun canCollectLeft(env: Env, _indice: Int, _floor: Int, see: List<List<String>>, inventory: MutableMap<String, Int>, action: Action): Boolean {
		var indice = _indice
		var floor = _floor

		action.turnLeft(env)
		while (floor-- > 0) {
			action.advance(env)
			if (!canCollect(env, see[--indice], inventory, action))
				return false
		}
		action.turnRight(env)
		action.turnRight(env)
		floor = _floor
		while (floor-- > 0)
			action.advance(env)
		action.turnLeft(env)
		return true
	}

}