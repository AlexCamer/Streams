import scala.collection.mutable

trait Publisher[A] {
  private val subscribers = mutable.SortedMap[Int, mutable.Buffer[Subscriber[A]]]()

  def publish(message: A): Unit =
    subscribers.values.flatten.foreach(_.notify(message))

  def subscribe(subscriber: Subscriber[A], priority: Int = 0): Unit =
    subscribers.get(-priority) match {
      case Some(buffer) => buffer.append(subscriber)
      case None => subscribers.addOne(-priority, mutable.Buffer(subscriber))
    }
}
