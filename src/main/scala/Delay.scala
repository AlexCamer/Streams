import scala.collection.mutable

final case class Delay[A](delay: Int) extends Stream[A, A] {
  require(delay > 0)

  private val queue = mutable.ArrayDeque[A]()

  override def notify(message: A): Unit = {
    queue.append(message)
    if (queue.length > delay)
      publish(queue.removeHead())
  }
}
