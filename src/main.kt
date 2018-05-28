
fun main(args: Array<String>) = "One, Two, Three, Four".split(",").map { it.trim() }.forEach { println(it) }

// fun main(args: Array<String>) = println(listOf("One", "Two", "Three", "Four").joinToString(" "))
