import CODE.OK
import kotlin.math.pow
import kotlin.system.exitProcess
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
        val inventory = action.inventory().also { println(it) }
        val see = action.see()
        if (action.connectNbr() > 0) action.fork()

        while (i < see.size) {
            println("I $i floor $floor SIZE ${see.size}")
            doCollecte(see[i], inventory, action)

            collectRight(i, floor, see, inventory, action)
            collectLeft(i, floor, see, inventory, action)

            if (canIncantate(action, inventory)) break

            i = ++floor * (floor + 1)
        }
        exitProcess(0)
    }

    private fun canIncantate(action: Action, inventory: MutableMap<String, Int>): Boolean {
        when {
            checkInventory(action, inventory) -> return doBroadcast(action)
            checkBroadcast(action) -> return goBroadcast(action)
        }
        return false
    }

    private fun checkInventory(action: Action, inventory: MutableMap<String, Int>): Boolean {
        for ((res, value) in levels[Env.level])
            if (inventory.containsKey(res) && inventory[res]!! < value) return false
        return true
    }

    private fun checkBroadcast(action: Action): Boolean {
        while (Env.broadcast.size > 0) {
            if (Env.broadcast[0].first == Env.level) return true
            Env.broadcast.remove(Env.broadcast.first())
        }
        return false
    }

    private fun goBroadcast(action: Action): Boolean {
        while (Env.broadcast.size > 0) {
            if (Env.broadcast[0].first == Env.level) {
                when (Env.broadcast[0].second) {
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
            }
            Env.broadcast.remove(Env.broadcast.first())
        }
        return false
    }

    private fun doBroadcast(action: Action): Boolean {

        levels[Env.level - 1].forEach { res, nbr ->
            var n = nbr
            while (n-- > 0) action.put(res)
        }

        while (action.inventory()[Resource.RESOURCE.PLAYER.value]!! < players[Env.level - 1])
            action.broadcast(Env.level.toString())
        return true
    }

    private fun doCollecte(resources: List<String>, inventory: MutableMap<String, Int>, action: Action) {
        println("doCollecte")
        resources.forEach {
            if (Resource.getMaxStones(RESOURCE.valueOf(it.toUpperCase())) > inventory[it]!!)
            {
                println("TKE $it")
                if (action.take(it) == OK) inventory[it] = inventory[it]!! + 1
            }
        }
        action.inventory().also { println(it) }
    }

    private fun collectRight(_indice: Int, _floor: Int, see: List<List<String>>, inventory: MutableMap<String, Int>, action: Action) {
        println("collectRight")
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
        action.inventory().also { println(it) }
    }

    private fun collectLeft(_indice: Int, _floor: Int, see: List<List<String>>, inventory: MutableMap<String, Int>, action: Action) {
        println("collectLeft")
        var indice = _indice
        var floor = _floor

        action.turnLeft()
       // println("Floor $floor indice $indice")
        while (floor-- > 0) {
            action.advance()
        //    println("SEE SIZE ${see.size} - Indice ${indice - 1}")
            doCollecte(see[--indice], inventory, action)
        }
        action.turnRight()
        action.turnRight()
        floor = _floor
        while (floor-- > 0) action.advance()
        action.turnLeft()
        action.inventory().also { println(it) }
    }

}