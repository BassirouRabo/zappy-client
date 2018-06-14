import CODE.OK
import kotlin.math.pow


class State {

    fun walk(action: Action) {
        var floor = 0
        var i = 0
        val inventory = action.inventory()
        val see = action.see()
        if (action.connectNbr() > 0) action.fork()

        while (i < see.size) {
            doCollecte(see[i], inventory, action)

            collectRight(i, floor, see, inventory, action)
            collectLeft(i, floor, see, inventory, action)

            if (canIncantate(action, inventory)) break

            i = i.toDouble().pow(floor++).toInt()
        }
    }

    private fun canIncantate(action: Action, inventory: MutableMap<String, Int>): Boolean {
        when {
            checkInventory(action, inventory) -> return doBroadcast(action)
            checkBroadcast(action) -> return goBroadcast(action)
        }
        return false
    }

    private fun checkInventory(action: Action, inventory: MutableMap<String, Int>): Boolean {

        val levels: Array<Map<String, Int>> = arrayOf(
                mapOf("linemate" to 1, "deraumere" to 0, "sibur" to 0, "mendiane" to 0, "phiras" to 0, "thystame" to 0),
                mapOf("linemate" to 1, "deraumere" to 1, "sibur" to 1, "mendiane" to 0, "phiras" to 0, "thystame" to 0),
                mapOf("linemate" to 2, "deraumere" to 0, "sibur" to 1, "mendiane" to 0, "phiras" to 2, "thystame" to 0),
                mapOf("linemate" to 1, "deraumere" to 1, "sibur" to 2, "mendiane" to 0, "phiras" to 1, "thystame" to 0),
                mapOf("linemate" to 1, "deraumere" to 2, "sibur" to 1, "mendiane" to 3, "phiras" to 0, "thystame" to 0),
                mapOf("linemate" to 1, "deraumere" to 2, "sibur" to 3, "mendiane" to 0, "phiras" to 1, "thystame" to 0),
                mapOf("linemate" to 2, "deraumere" to 2, "sibur" to 2, "mendiane" to 2, "phiras" to 2, "thystame" to 1)
        )

        for ((res, value) in levels[Env.level])
            if (inventory.containsKey(res) && inventory[res]!! < value) return false

        return true
    }

    private fun checkBroadcast(action: Action): Boolean {
        return true
    }

    private fun goBroadcast(action: Action): Boolean {
        return true
    }

    private fun doBroadcast(action: Action): Boolean {
        return true
    }

    private fun doCollecte(resources: List<String>, inventory: MutableMap<String, Int>, action: Action) {
        resources.forEach {
            if (Resource.getMaxStones() > inventory[it]!!)
                if (action.take(it) == OK) inventory[it] = inventory[it]!! + 1
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