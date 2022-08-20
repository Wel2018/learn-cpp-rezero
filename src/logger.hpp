#include "base.h"

static stringstream ss;

class Logger : public noncopyable 
{
public:
    void _info(const string& msg) {
        printd("[%s] %s", get_time(), msg.c_str());
    }

    // Usage:
    // logger._info("% % %", "hello", 123, 3.14);
    template<typename T, typename... Targs>
    void _info(const char* format, T value, Targs... Fargs) 
    {
        string_fmt(ss, format, value, Fargs...); // format all args
        _info(ss.str()); // output
        ss.str(""); // clear buff
    }

    void string_fmt(stringstream& ss, const char* format) { ss << format; }

    template<typename T, typename... Targs>
    void string_fmt(stringstream& ss, const char* format, T value, Targs... Fargs) 
    {
        for ( ; *format != '\0'; format++ ) {
            if ( *format == '%' ) {
               ss << value;
               string_fmt(ss, format+1, Fargs...);
               return;
            }
            ss << *format;
        }
    }

public:
    Logger() {
        ss.clear();
    }

    static Logger& get_instance() {
        static Logger logger;
        return logger;
    }

    virtual void log(const string&& msg, 
                     const string&& file, 
                     const string&& func, 
                     const int&& line) {
        this->_info("% %() - #%", file, func, line);
        if(msg.size() > 0) 
            cout << " | " << msg << endl;
        else cout << endl;
    }
};

// some useful macros
#define INIT_GLOBAL_LOGGER() decltype(auto) logger = Logger::get_instance()
#define LOG(msg) logger.log(msg, __FILE__, __func__, __LINE__)
