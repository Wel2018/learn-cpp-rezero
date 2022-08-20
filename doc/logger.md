# Logger 

In the following example,

```cpp
#include "logger.hpp"

INIT_GLOBAL_LOGGER();

...

int main() {
    LOG("hello world, this is main()");
    foo();
    bar();
    logger._info("% % %\n", "hello", 123, 3.14);
}
```
it will output:

```
[2022-08-20 16:30:00] test/test_logger.cpp main() - #16 | hello world, this is main()
[2022-08-20 16:30:00] test/test_logger.cpp foo() - #8 | hello, this is foo()
[2022-08-20 16:30:00] test/test_logger.cpp bar() - #12 | hello, this is bar()
[2022-08-20 16:30:00] hello 123 3.14
```

You can use `LOG(msg)` to easily output LOG information, 
or you can use the low-level api `_info` and `%` to easily format as you want.

There are several useful macros in the `logger.hpp` as following:

```c
#define INIT_GLOBAL_LOGGER() decltype(auto) logger = Logger::get_instance()
#define LOG(msg) logger.log(msg, __FILE__, __func__, __LINE__)
```

The `LOG(msg)` macro use the virtual method `Logger::log()`, 
so you can override it by using your own implementation.
