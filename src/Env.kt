import java.io.DataInputStream
import java.net.Socket

object Env {
    var name : String = ""
    var port : Int = 0
    var host : String = ""
    var time : Int = 1260
    var client : Socket = Socket()
    var broadcast : String = ""
    var level = 1
}