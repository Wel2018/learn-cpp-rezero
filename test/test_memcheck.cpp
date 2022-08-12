#include "memcheck.hpp"

int main()
{
    
    decltype(auto) R = Registry::get_instance();
    char   *m1 = new char; 
    int    *m2 = new int(100);  // not free
    double *m3 = new double;
    delete m1;
    delete m3;
    R.memcheck();
}

/* 输出：
[file: test/test_memcheck.cpp - line 7] malloc 1 bytes at 0x561934d1beb0
[file: test/test_memcheck.cpp - line 8] malloc 4 bytes at 0x561934d1c3b0
[file: test/test_memcheck.cpp - line 9] malloc 8 bytes at 0x561934d1c430
free 0x561934d1beb0 which allocated at 7
free 0x561934d1c430 which allocated at 9
detect 1 memory leak points:
addr: 0x561934d1c3b0, line: 8
*/
