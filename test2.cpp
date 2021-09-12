#include "test.hpp"

namespace test_ns {
    thread_local int a;
}

void test_a() { std::cout << test_ns::a << std::endl; }