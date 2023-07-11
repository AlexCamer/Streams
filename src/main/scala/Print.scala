final case class Print[A]() extends Subscriber[A] {
  override def notify(message: A): Unit = println(message)
}
