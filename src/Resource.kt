object Resource {
    val linemate : String = "linemate"
    val deraumere : String = "deraumere"
    val sibur : String = "sibur"
    val mendiane : String = "mendiane"
    val phiras : String = "phiras"
    val thystame : String = "thystame"
    val nourriture : String = "nourriture"

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
        return mutableMapOf(linemate to 0, deraumere to 0, sibur to 0, mendiane to 0, phiras to 0, thystame to 0, nourriture to 0)
    }

    fun isStone(stone : String) : Boolean = getStones().contains(stone)

}