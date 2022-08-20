#include "logger.hpp"

INIT_GLOBAL_LOGGER();

// test 

void foo() {
    LOG("hello, this is foo()");
}

void bar() {
    LOG("hello, this is bar()");
}

int main() {
    // You can use `LOG(msg)` to easily output LOG information 
    LOG("hello world, this is main()");
    foo();
    bar();
    // Or you can use the low-level api `_info` and `%` to easily format as you want
    logger._info("% % %\n", "hello", 123, 3.14);
}
