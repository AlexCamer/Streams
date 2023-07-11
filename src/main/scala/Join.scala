final case class JoinBuffer[A](var buffer: Option[A] = None) extends Stream[A, Unit] {
  override def notify(message: A): Unit = {
    buffer = Some(message)
    publish()
  }
}

final case class Join2[A, B]() extends Publisher[(A, B)] {
  val _1: JoinBuffer[A] = JoinBuffer()
  val _2: JoinBuffer[B] = JoinBuffer()

  private object internal extends Subscriber[Unit] {
    override def notify(message: Unit): Unit = (_1, _2) match {
      case (
        JoinBuffer(Some(a)),
        JoinBuffer(Some(b))
      ) => publish((a, b))
      case _ =>
    }
  }

  internal.subscribeTo(_1)
  internal.subscribeTo(_2)

  def resetOn[C](publisher: Publisher[C], priority: Int = 1): Unit = {
    new Subscriber[C] {
      override def notify(message: C): Unit = {
        _1.buffer = None
        _2.buffer = None
      }
    }.subscribeTo(publisher, priority)
  }
}

final case class Join3[A, B, C]() extends Publisher[(A, B, C)] {
  val _1: JoinBuffer[A] = JoinBuffer()
  val _2: JoinBuffer[B] = JoinBuffer()
  val _3: JoinBuffer[C] = JoinBuffer()

  private object internal extends Subscriber[Unit] {
    override def notify(message: Unit): Unit = (_1, _2, _3) match {
      case (
        JoinBuffer(Some(a)),
        JoinBuffer(Some(b)),
        JoinBuffer(Some(c))
      ) => publish((a, b, c))
      case _ =>
    }
  }

  internal.subscribeTo(_1)
  internal.subscribeTo(_2)
  internal.subscribeTo(_3)

  def resetOn[D](publisher: Publisher[D], priority: Int = 1): Unit = {
    new Subscriber[D] {
      override def notify(message: D): Unit = {
        _1.buffer = None
        _2.buffer = None
        _3.buffer = None
      }
    }.subscribeTo(publisher, priority)
  }
}

final case class Join4[A, B, C, D]() extends Publisher[(A, B, C, D)] {
  val _1: JoinBuffer[A] = JoinBuffer()
  val _2: JoinBuffer[B] = JoinBuffer()
  val _3: JoinBuffer[C] = JoinBuffer()
  val _4: JoinBuffer[D] = JoinBuffer()

  private object internal extends Subscriber[Unit] {
    override def notify(message: Unit): Unit = (_1, _2, _3, _4) match {
      case (
        JoinBuffer(Some(a)),
        JoinBuffer(Some(b)),
        JoinBuffer(Some(c)),
        JoinBuffer(Some(d))
      ) => publish((a, b, c, d))
      case _ =>
    }
  }

  internal.subscribeTo(_1)
  internal.subscribeTo(_2)
  internal.subscribeTo(_3)
  internal.subscribeTo(_4)

  def resetOn[E](publisher: Publisher[E], priority: Int = 1): Unit = {
    new Subscriber[E] {
      override def notify(message: E): Unit = {
        _1.buffer = None
        _2.buffer = None
        _3.buffer = None
        _4.buffer = None
      }
    }.subscribeTo(publisher, priority)
  }
}
