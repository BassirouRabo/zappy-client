object Resource {
    const val linemate = "linemate"
    const val deraumere = "deraumere"
    const val sibur = "sibur"
    const val mendiane = "mendiane"
    const val phiras = "phiras"
    const val thystame = "thystame"
    const val food = "food"

    enum class RES {
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
        FOOD
    }

    fun getStones() : List<String> {
        return listOf(linemate, deraumere, sibur, mendiane, phiras, thystame)
    }

    fun getStonesMap() : MutableMap<String, Int>{
        return mutableMapOf(linemate to 0, deraumere to 0, sibur to 0, mendiane to 0, phiras to 0, thystame to 0, food to 0)
    }

    fun isStone(stone : String) : Boolean = getStones().contains(stone)

}