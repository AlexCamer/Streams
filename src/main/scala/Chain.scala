final case class Chain[A, B](tail: Publisher[B]) {
  def link[C](stream: Stream[B, C]): Chain[A, C] = {
    tail.subscribe(stream)
    Chain(stream)
  }

  def link(subscriber: Subscriber[B]): Unit =
    tail.subscribe(subscriber)
}

