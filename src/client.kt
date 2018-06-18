
fun main(args: Array<String>) {
    val action = Action()
    val state = State()

    if (args.size != 3) { Print.printUsage() }

    Env.init(args)

    if (Env.nbClient > 1)
        while (Env.level < 7) state.walk(action)

    Env.client.close()

    // action.see().forEach { println(it) }

    /*  action.take(FOOD.value)

      action.inventory().forEach { key, value -> println("$key -> $value") }

      action.put(FOOD.value)

      action.inventory().forEach { key, value -> println("$key -> $value") }

      action.kick()*/

}
