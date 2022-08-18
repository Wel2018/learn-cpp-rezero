#ifndef _DEBUG_H
#define _DEBUG_H

#include <cstdio>

#define ASSERT_(expr, msg) \
    if (!(expr)) puts(msg);

#ifdef DEBUG
#define printd(fmt, args...) printf(fmt, ##args)
#else
#define printd(fmt, args...)
#endif

#define COUT(x) std::cout << x << std::endl

#endif /* _DEBUG_H */

