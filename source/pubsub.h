#pragma once

#include <map>
#include <type_traits>
#include <utility>
#include <vector>

namespace streams {

template <class Message>
class Publisher;

template <class Message>
class Subscriber {
public:
    void subscribe_to(Publisher<Message>& publisher, int priority = 0);
    virtual void notify(const Publisher<Message>& publisher) {}
};

template <class Message>
class Publisher {
public:
    void subscribe(Subscriber<Message>& subscriber, int priority = 0) {
        m_subscribers[priority].emplace_back(&subscriber);
    }

    const Message& message() const { return m_message; }

protected:
    template <class Type>
    void publish(Type&& message) {
        static_assert(std::is_convertible_v<Type, Message>);
        m_message = std::forward<Message>(message);
        for (auto it = m_subscribers.rbegin(); it != m_subscribers.rend(); ++it) {
            for (auto& subscriber: it->second)
                subscriber->notify(*this);
        }
    }

private:
    std::map<int, std::vector<Subscriber<Message>*>> m_subscribers;
    Message m_message;
};

template <class Message>
void Subscriber<Message>::subscribe_to(Publisher<Message>& publisher, int priority) {
    publisher.subscribe(*this, priority);
}

}
