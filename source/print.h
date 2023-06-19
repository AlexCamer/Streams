#pragma once

#include <iostream>
#include "pubsub.h"

namespace streams {

template <class Message>
struct Print : Subscriber<Message> {
    Print(std::ostream& out = std::cout) : m_out{ out } {}
    virtual void notify(const Message &message) override { m_out << message << "\n"; }

private:
    std::ostream& m_out;
};

}
