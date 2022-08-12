/*
* Learn C++ Re:Zero
*/

#ifndef _STD_HEADER_H
#define _STD_HEADER_H

#ifndef __cplusplus // C header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#else //  C++ header

#include <bits/stdc++.h>

#include <malloc.h>
#include <string.h>
#include <cassert>

#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <type_traits>
#include <functional>
#include <future>
#include <algorithm>
#include <fstream>
#include <exception>
#include <atomic>

using namespace std;

#endif /* __cplusplus */

#include "debug.h"
#include "util.h"

#endif // _STD_HEADER_H
