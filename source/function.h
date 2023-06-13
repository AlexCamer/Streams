#pragma once

#include "stream.h"

namespace streams {

template <class Input, class Output>
class Function : public Stream<Input, Output> {
public:
    Function(std::function<Output(const Input&)> function) : m_function{ function } {}

    virtual void notify(const Publisher<Input>& publisher) override {
        this->publish(m_function(publisher.message()));
    }

private:
    std::function<Output(const Input&)> m_function;
};

}