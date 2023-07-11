final case class Clock() extends Publisher[Int] {
  def start(): Unit = LazyList.from(0).foreach(publish)
}
