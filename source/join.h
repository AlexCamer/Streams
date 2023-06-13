#pragma once

#include <tuple>
#include "stream.h"

namespace streams {

template<class... Messages>
class Join : private Subscriber<size_t>, public Publisher<std::tuple<Messages...>> {
private:
    std::tuple<Publisher<Messages>*...> m_publishers;
    size_t m_count;

    virtual void notify(const Publisher<size_t>& publisher) override {
        m_count += publisher.message();
        if (m_count == std::tuple_size_v<decltype(m_publishers)>)
            this->publish();
    }
};

}
