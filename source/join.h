#pragma once

#include <any>
#include <array>
#include <tuple>
#include <utility>
#include "stream.h"

namespace streams {

template <class... Inputs>
class Join : private Subscriber<std::pair<bool, bool>>, public Publisher<std::tuple<Inputs...>> {
    using Output = typename std::tuple<Inputs...>;

    template <std::size_t Index>
    using Input = typename std::tuple_element_t<Index, Output>;

public:
    template <std::size_t Index>
    void subscribe(Publisher<Input<Index>> &publisher) { std::get<Index>(m_subscribers).subscribe(publisher, 0); }

    template <class Input>
    void reset(Publisher<Input> &publisher) { internal_reset(publisher, std::index_sequence_for<Inputs...>{}); }

private:
    static constexpr std::size_t Size = std::tuple_size_v<Output>;
    using InternalMessage = typename std::pair<bool, bool>;

    enum InternalState : bool {
        READY,
        WAITING
    };

    struct InternalReset : Stream<std::any, InternalMessage> {
        InternalState m_state = WAITING;

        virtual std::optional<InternalMessage> update(const std::any &any) override {
            InternalState prev = m_state;
            m_state = WAITING;
            return std::make_pair(prev, m_state);
        }
    };

    template <class Input>
    struct InternalSubscriber : Stream<Input, InternalMessage> {
        InternalReset m_reset;
        InternalState &m_state = m_reset.m_state;
        Input m_input;

        virtual std::optional<InternalMessage> update(const Input &input) override {
            m_input = input;
            InternalState prev = m_state;
            m_state = READY;
            return std::make_pair(prev, m_state);
        }
    };

    std::tuple<InternalSubscriber<Inputs>...> m_subscribers;
    std::size_t m_count = 0;

    virtual void notify(const InternalMessage &message) override {
        if (message.first == WAITING) {
            if (message.second == READY)
                m_count++;
        } else if (message.second == WAITING)
            m_count--;
        if (m_count == Size)
            internal_publish(std::index_sequence_for<Inputs...>{});
    }

    template <class Input, std::size_t... Indices>
    void internal_reset(Publisher<Input> &publisher, std::index_sequence<Indices...>) {
        (std::get<Indices>(m_subscribers).m_reset.subscribe(publisher), ...);
    }

    template <std::size_t... Indices>
    void internal_publish(std::index_sequence<Indices...>) {
        this->publish(std::make_tuple(std::get<Indices>(m_subscribers).m_input...));
    }
};

}