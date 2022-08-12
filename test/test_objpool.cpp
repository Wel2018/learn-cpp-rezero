#include "objpool.hpp"

class MyObj : public Object {
public:
    void hello() { puts("hello"); }
};

int main()
{
    ObjectPool<MyObj> pool;
    for(int i = 0; i < 5; i++) {
        pool.show_objpool_info();
        auto obj1 = pool.request_object(); 
        auto obj2 = pool.request_object(); 
        auto obj3 = pool.request_object(); 
        pool.return_object(obj1); 
    }
}

