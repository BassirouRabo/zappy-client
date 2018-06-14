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

            if (canIncantate(action)) break

            i = i.toDouble().pow(floor++).toInt()
        }
    }

    private fun canIncantate(action: Action): Boolean {
        when {
            checkInventory(action) -> return doBroadcast(action)
            checkBroadcast(action) -> return goBroadcast(action)
        }
        return false
    }

    private fun checkInventory(action: Action): Boolean {
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