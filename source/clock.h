#pragma once

#include <any>
#include "stream.h"

namespace streams {

class Clock : public Publisher<int> {
public:
    void start() {
        for (int i = 0;; i++)
            publish(i);
    }
};

}