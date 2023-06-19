#pragma once

#include <functional>
#include "stream.h"

namespace streams {

template <class Input, class Output>
class Function : public Stream<Input, Output> {
public:
    Function(std::function<Output(const Input &)> &&function) : m_function{ std::move(function) } {}
    virtual std::optional<Output> update(const Input &input) override { return m_function(input); }

private:
    std::function<Output(const Input &)> m_function;
};

}