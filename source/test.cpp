// #include "stream.h"
// using namespace streams;

#include <utility>

int main() {
    std::pair<bool, bool> p{ true, false };
    switch (p) {
        case std::pair{ true, true }:
            break;
    }
    return 0;
}
