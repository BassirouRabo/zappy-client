import Print.printError

data class Broadcast(var origin : Int = 0, var id: Int = 0, var code : Int = 0, var level: Int = 0)

fun messageToBroadcast(res: String) : Broadcast {
	val map = res.split(",").map { it.trim() }
	if (map.size != 2 || map[1].length != 4)  printError("handleBroadcast#:$res map.size${map.size} map[1].length${map[1].length}")

	try {
		val origin = map[0].toInt()
		val id = map[1].substring(0, 2).toInt()
		val code = map[1].substring(2, 3).toInt()
		val level = map[1].substring(3, 4).toInt()
		return Broadcast(origin = origin, id = id, code = code, level = level)
	} catch (e: NumberFormatException) { printError("handleBroadcast:$res") }
	return Broadcast()
}