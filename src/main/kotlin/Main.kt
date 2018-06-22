fun main(args: Array<String>) {
	if (args.size != 3)
		printUsage()

	val action = Action()
	val state = State()
	val env = Env()

	env.init(env, args)
	if (env.nbClient > 0)
		while (env.level < 7) state.walk(env, action)
	env.client.close()

}
