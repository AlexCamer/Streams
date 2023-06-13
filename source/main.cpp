#include <chrono>
#include <iostream>
#include "clock.h"
#include "function.h"
#include "print.h"

int x2_function(const int& x) {
    return x * 2;
}

int main() {
    using namespace streams;

    Clock clock{};

    Function<int, int> x2{ x2_function };
    x2.subscribe_to(clock);

    Print<int> print{};
    print.subscribe_to(x2);

    clock.start();
    return 0;
}
