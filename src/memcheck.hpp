// 内存泄露检测

#include "base.h"

string get_address(void* p);

#define debug_new(p, size) \
    printd("[file: %s - line %d] malloc %ld bytes at %p\n", file, line, size, p)

// 内存申请时的记录注册中心
class Registry final : public noncopyable {
    using addr_t = std::string;
    using line_t = std::string;
    unordered_map <addr_t, line_t> registry; 

public:
    void add(string k, string v) {
        registry[k] = v;
    }

    void remove(string k) {
        if(!registry.count(k)) return;
        registry.erase(string(k));
    }

    // 获取该内存块申请的代码行位置
    const char* get(string k) {
        if(!registry.count(k)) return "not found";
        return registry[k].c_str();
    }

    virtual void memcheck()
    {
        if(registry.empty()) {
            printd("no heap memory leak detect, :D");
            return;
        }
        printf("notice: detect %ld memory leak point(s) at \n", registry.size());
        for(auto& [addr, line]: registry) {
            printf("addr: %s, line: %s\n", addr.c_str(), line.c_str());
        }
    }

    void check_registry_size() {
        printd("registry size: %ld\n", registry.size());
    }

    static Registry& get_instance() {
        static Registry R;
        return R;
    }
};

// 将地址值转换为字符串类型
string get_address(void* p) {
    char addr[100];
    sprintf(addr, "%p", p);
    return string(addr);
}

// new 运算符重载
void* operator new(std::size_t size, const char* file, int line) {
    string val = to_string(line);
    void* p = (void*) malloc(size);
    debug_new(p, size);
    decltype(auto) R = Registry::get_instance();
    R.add(get_address(p), val);
    return p;
}

void free_pointer(void* p, const char* file, int line) {
    auto addr = get_address(p);
    decltype(auto) R = Registry::get_instance();
    if(R.get(addr) == "not found") return;
    printd("free %s which allocated at %s\n", addr.c_str(), R.get(addr));
    R.remove(addr);
    free(p);
}

// delete 运算符重载
void operator delete(void* ptr) noexcept { 
    free_pointer(ptr, nullptr, 0); 
}

#define new new(__FILE__, __LINE__)

