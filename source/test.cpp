#include <iostream>
#include <map>
#include <type_traits>
#include <vector>
using namespace std;

template <class T, class... U>
class Test {
public:
    T test(U... x) {
        return x...;
    }
};

int main() {
    Test<int(int)> test{};
    std::cout << test.test(1) << "\n";
    return 0;
}