#pragma once

#include "stream.h"

namespace streams {

struct Clock : Publisher<int> {
    void start() {
        for (int i = 0;; i++)
            publish(i);
    }
};

}