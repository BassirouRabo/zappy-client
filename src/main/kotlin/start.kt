import java.util.*
import kotlin.system.exitProcess

fun printUsage() {
	println("Client Usage: ./client \n\t-n <team> \n\t-p <port> \n\t[-h <hostname>]")
	exitProcess(-1)
}

fun main(args: Array<String>) {

	if (args.size != 3)
		printUsage()

	while (true) {
		try {
			val proc =  ProcessBuilder("java", "-jar", "../../../build/libs/client-1.0.jar", args[0], args[1], args[2]).start()
			Scanner(proc.inputStream).use {
				while (it.hasNextLine()) println(it.nextLine())
			}
			Thread.sleep(5000)
		} catch (e: Exception) {
			println("${e.message}")
		}
	}
}