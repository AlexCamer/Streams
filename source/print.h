#pragma once

#include <iostream>
#include "stream.h"

namespace streams {

template <class Message>
class Print : public Subscriber<Message> {
public:
    Print(std::ostream& out = std::cout) : m_out{ out } {}

    virtual void notify(const Publisher<Message>& publisher) override {
        m_out << publisher.message() << "\n";
    }

private:
    std::ostream& m_out;
};

}
