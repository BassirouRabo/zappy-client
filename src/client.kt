import Print.printError
import java.net.*
import java.io.*
import Message.getMessage
import Message.sendMessage

fun main(args: Array<String>) {
    val action = Action()

    if (args.size != 3) { Print.printUsage() }

    Env.init(args)

    action.see().forEach { println(it) }

    action.take(Resource.food)

    action.inventory().forEach { key, value -> println("$key -> $value") }

    action.put(Resource.food)

    action.inventory().forEach { key, value -> println("$key -> $value") }

    action.kick()

    Env.client.close()
}