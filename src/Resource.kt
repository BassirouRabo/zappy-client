object Resource {

    enum class RESOURCE(val value: String) {
        LINEMATE("linemate"),
        DERAUMERE("deraumere"),
        SIBUR("sibur"),
        MENDIANE("mendiane"),
        PHIRAS("phiras"),
        THYSTAME("thystame"),
        FOOD("nourriture") // food
    }

    fun getStones() : List<String> {
        return listOf(RESOURCE.LINEMATE.value, RESOURCE.DERAUMERE.value, RESOURCE.SIBUR.value, RESOURCE.MENDIANE.value, RESOURCE.PHIRAS.value, RESOURCE.THYSTAME.value, RESOURCE.FOOD.value)
    }

    fun getStonesMap() : MutableMap<String, Int>{
        return mutableMapOf(RESOURCE.LINEMATE.value to 0, RESOURCE.DERAUMERE.value to 0, RESOURCE.SIBUR.value to 0, RESOURCE.MENDIANE.value to 0, RESOURCE.PHIRAS.value to 0, RESOURCE.THYSTAME.value to 0, RESOURCE.FOOD.value to 0)
    }

    fun isStone(stone : String) : Boolean = getStones().contains(stone)

    fun getMaxStones(): Int = 1

}



