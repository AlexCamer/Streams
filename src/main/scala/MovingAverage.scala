import scala.collection.mutable

final case class MovingAverage[A](size: Int)(implicit fractional: Fractional[A]) extends Stream[A, A] {
  require(size > 0)

  private val queue = mutable.ArrayDeque[A]()
  private var sum = fractional.zero

  override def notify(message: A): Unit = {
    queue.append(message)
    sum = fractional.plus(sum, message)
    if (queue.length >= size) {
      if (queue.length > size)
        sum = fractional.minus(sum, queue.removeHead())
      publish(fractional.div(sum, fractional.fromInt(size)))
    }
  }
}
