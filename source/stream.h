#pragma once

#include <optional>
#include "pubsub.h"

namespace streams {

template <class Input, class Output>
class Stream : public Subscriber<Input>, public Publisher<Output> {
public:
    virtual std::optional<Output> update(const Input &input) = 0;

private:
    virtual void notify(const Input &input) override {
        if (auto output = update(input))
            this->publish(*output);
    }
};

}
