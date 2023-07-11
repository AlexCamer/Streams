object Test {
  def main(args: Array[String]): Unit = {
    val clock = Clock()

    val join = Join3[Int, Int, Int]()
    join._1.subscribeTo(clock)
    join._2.subscribeTo(clock)
    join._3.subscribeTo(clock)
    join.resetOn(clock)

    val print = Print[(Int, Int, Int)]()
    print.subscribeTo(join)

    clock.start()
  }
}
