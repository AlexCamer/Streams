trait Subscriber[A] {
  def notify(message: A): Unit

  def subscribeTo(publisher: Publisher[A], priority: Int = 0): Unit =
    publisher.subscribe(this, priority)
}
