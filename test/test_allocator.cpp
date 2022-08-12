#include "allocator.hpp"

void test_stl_allocator()
{
    allocator<string> alloc;
    // 只分配内存，不调用构造函数
    auto const head = alloc.allocate(1024); 
    auto p = head;
    decltype(auto) cp = head; 

    // 手动调用构造
    alloc.construct(p++, "hello");
    alloc.construct(p++, 10, 'c');

    // 此时 p 落在下一个已申请内存但没有调用构造的位置
    assert(head[0] == "hello");
    assert(head[1] == "cccccccccc");

    // 对于前两个已经初始化的位置调用析构，释放（只能对已经构造过的内存使用析构）
    alloc.destroy(head + 0);
    alloc.destroy(head + 1);
    
    // 将申请的这段内存归还给系统
    alloc.deallocate(head, 1024);
}

// 提供访问空间分配器属性的一般方式
void test_allocator_traits() 
{
    allocator<string> alloc;
    using traits = allocator_traits<decltype(alloc)>;
    using value_type = traits::value_type;  // string
    using pointer = traits::pointer;  // string*
}

// 测试自定义的空间分配器 Jallocator
void test_imp_allocator()
{
    Jallocator<string> alloc;
    auto const head = alloc.alloc(1024); 
    auto p = head; 

    alloc.construct(p++, "hello");

    cout << head[0] << endl;   
    cout << head[1] << endl;  

    alloc.deconstruct(head + 0);
    alloc.deconstruct(head + 1);
    alloc.dealloc(head, 1024);
}

int main()
{
    test_stl_allocator();
    test_imp_allocator();
}
