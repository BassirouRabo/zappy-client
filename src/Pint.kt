import kotlin.system.exitProcess

object Print {
    fun usage() = println("Usage: ./client \n\t-n <team> \n\t-p <port> \n\t[-h <hostname>]")

    fun error_port() = println("Port cant't be [0 - 1023]")

    fun printError(msg: String) {
        println("ERROR MESSAGE FOR COMMAND $msg")
        exitProcess(-1)
    }
}