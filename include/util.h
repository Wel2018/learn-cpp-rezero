#ifndef _UTIL_H
#define _UTIL_H

#include <ctime>    // for time, localtime, asctime
#include <unistd.h> // for sleep

// 获取当前系统时间（格式：亚洲格式 iso8601，形如 2022-08-12 00:00）
inline char* get_time() {
    static char timebuf[30];
    time_t nowtime = time(nullptr);
	struct tm *local = localtime(&nowtime); 
	strftime(timebuf, 30, "%Y-%m-%d %H:%M:%S", local);
    return timebuf;
}

// 用于实现单例模式
class noncopyable
{
protected:
    noncopyable() = default;
    ~noncopyable() = default;

public:
    noncopyable( const noncopyable& ) = delete;
    noncopyable& operator=( const noncopyable& ) = delete;
};

#endif // _UTIL_H
