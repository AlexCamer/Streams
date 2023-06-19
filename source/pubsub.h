#pragma once

#include <functional>
#include <map>
#include <vector>

namespace streams {

template <class Message>
class Publisher;

template <class Message>
class Subscriber {
public:
    void subscribe(Publisher<Message> &publisher, int priority = 0);
    virtual void notify(const Message &message) = 0;
};

template <class Message>
class Publisher {
protected:
    void publish(const Message &message) {
        for (auto &priority: m_subscribers) {
            for (auto &subscriber: priority.second)
                subscriber->notify(message);
        }
    }

private:
    friend class Subscriber<Message>;
    std::map<int, std::vector<Subscriber<Message> *>, std::greater<int>> m_subscribers;
};

template <class Message>
void Subscriber<Message>::subscribe(Publisher<Message> &publisher, int priority) {
    publisher.m_subscribers[priority].emplace_back(this);
}

}
