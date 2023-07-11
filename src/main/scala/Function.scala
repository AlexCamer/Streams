final case class Function[A, B](function: A => B) extends Stream[A, B] {
  override def notify(message: A): Unit = publish(function(message))
}
