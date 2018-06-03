object Stone {
    const val linemate : String = "linemate"
    const val deraumere : String = "deraumere"
    const val sibur : String = "sibur"
    const val mendiane : String = "mendiane"
    const val phiras : String = "phiras"
    const val thystame : String = "thystame"

    fun getStones() : List<String> {
        return listOf(linemate, deraumere, sibur, mendiane, phiras, thystame)
    }

    fun isStone(stone : String) : Boolean = getStones().contains(stone)

}