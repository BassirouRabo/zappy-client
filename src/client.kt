import Print.printError
import java.net.*
import java.io.*
import Message.getMessage
import Message.sendMessage

fun main(args: Array<String>) {
    val action = Action()

    if (args.size != 3) { Print.printUsage() }

    Env.init(args)

   // println("${Env.nbClient}\n${Env.x} ${Env.y}")

    action.see().forEach { println(it) }

//    action.turnLeft()

    action.inventory().forEach { key, value -> println("$key -> $value") }

    Env.client.close()
}