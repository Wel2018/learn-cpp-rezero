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

#endif /* _DEBUG_H */

