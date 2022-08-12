// 简单内存分配器

#include "base.h"

template <class T>
inline T* _alloc(int size, T*) {
    // Takes a replacement handler as the argument, returns the previous handler.
    set_new_handler(0);
    T* t = (T*) ( ::operator new((size_t)(size * sizeof(T))) );
    if(t == nullptr) {
        cerr << "alloc failed" << endl;
        exit(1);
    }
    return t;
}

template <class T>
inline void _dealloc(T* t) {
    if(t == nullptr) return;
    ::operator delete(t);
}

template <class T1, class T2>
inline void _construct(T1* t, const T2& val) {
    new(t) T2(val); // 在 t 这段内存使用 T2(val) 拷贝构造初始化
}

template <class T>
inline void _deconstruct(T* t) {
    t->~T();
}

// 空间分配器
template <class T>
class Jallocator {
public: 
    // ready
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& ref;
    typedef const T& const_ref;
    typedef size_t size_type;
    typedef ptrdiff_t diff_type;

    // rebind
    template<class U> struct rebind {
        typedef Jallocator<U> other;
    };

    // 分配 n 字节内存
    pointer alloc(size_type n, const void* hint=0) {
        return _alloc((diff_type)n, (pointer)0);
    }

    // 释放指针 p 指向的前 n 个字节的内存
    void dealloc(pointer p, size_type n) {
        _dealloc(p);
    }

    // 在指针 p 的位置调用拷贝构造函数，因此需要提供被拷贝的对象
    void construct(pointer p, const T& val) {
        _construct(p, val);
    }

    // 在指针 p 的位置调用析构函数
    void deconstruct(pointer p) { _deconstruct(p); }

    // 返回对象地址、最大可用内存
    pointer address(ref x) { return (pointer)(&x); }
    size_type max_size() const { return size_type(UINT_MAX / sizeof(T)); }
};
