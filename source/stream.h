#pragma once

#include <any>
#include <tuple>
#include "pubsub.h"

namespace streams {

template <class Output, class... Inputs>
class Stream : public Publisher<Output> {};
public:
private:
    Publisher<std::any> root;

    std::tuple<Publisher<Inputs>*...> m_publishers;
}
