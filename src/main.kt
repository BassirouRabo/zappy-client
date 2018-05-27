
fun main(args: Array<String>) {
    var person = Person("Bibi")
    person._name
}

class Person(name : String, var age : Int = 0) {
    var _name = name
    init {
        println("name $_name")
    }


}