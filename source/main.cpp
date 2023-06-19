#include <iostream>
#include "clock.h"
#include "function.h"
#include "join.h"
#include "print.h"
using namespace streams;

int main() {
    Clock clock{};

    Join<int, int> join{};
    join.subscribe<0>(clock);
    join.subscribe<1>(clock);
    join.reset(clock);

    Function<std::tuple<int, int>, int> add{ [](auto x) { return std::get<0>(x) + std::get<1>(x); } };
    add.subscribe(join);

    Print<int> print{};
    print.subscribe(add);

    clock.start();
    return 0;
}
