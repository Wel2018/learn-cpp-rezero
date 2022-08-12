// 对象池的简单实现

#include "base.h"

///////////////////////////////////////////////////////////////////////////////
// 对象基类

class Object {
    int count = 0;      // 引用计数
    // bool reusable;  // 是否回收到对象池
public:
    Object() {}
    virtual ~Object() {}
    int get_count() { return count; }
    void inc_count() { count++; }
    void dec_count() { count--; }
};

///////////////////////////////////////////////////////////////////////////////
// 对象工厂

template<typename ObjectType = Object>
class ObjectFactory {
    using OT = ObjectType;
public:
    virtual ~ObjectFactory() {}

    // 创建对象
    virtual OT* create() {
        printd("create obj\n");
        return new OT();
    }

    // 销毁对象
    virtual void destroy(OT* obj) {
        if(!obj) return;
        printd("destroy obj\n");
        delete obj;
    }
};

///////////////////////////////////////////////////////////////////////////////
// 对象池

template<typename T = Object>
class ObjectPool {
public:
    // 定义类型
    using ObjType = T;
    using OT = T;
    using PoolType = ObjectPool<ObjType>;
    using FactoryType = ObjectFactory<ObjType>;
    using ObjContainer = list<ObjType*>;

private:
    shared_ptr<FactoryType> factory;
    
    // 活跃对象、空闲对象的数量
    const int max_idle;
    const int max_actived; 
    volatile int n_actived; 
    volatile int n_idle;

    ObjContainer oc_idle;   // 空闲对象容器
    ObjContainer oc_active; // 正在使用中的对象列表
    mutex mtx;

public:
    // 限制对象池的最大空闲对象数，和正在使用中的对象的最大个数
    ObjectPool(int idle = 5, int active = 2) 
        : max_idle(idle), max_actived(active), n_actived(0), n_idle(0) 
    {
        factory = shared_ptr<FactoryType>();
        if(!factory) factory.reset(new FactoryType());
    }
    
    ~ObjectPool() {
        release_objects(true, true); // 释放所有对象
        printd("ObjectPool destroyed\n");
    }

    // 释放所有对象池内的对象（默认只释放 idle 对象以空出部分内存，正在使用中的暂时不释放）
    void release_objects(bool release_active = false, bool release_idle = true) 
    {
        if (release_active) { 
            for(auto obj : oc_active) factory->destroy(obj);
        }
        if (release_idle) {
            for(auto obj : oc_idle) factory->destroy(obj);
        }
    }

    // 打印对象池信息
    virtual void show_objpool_info() {
        printd("[active] nums/max : %d/%d | [idle] nums/max : %d/%d \n", 
            n_actived, max_actived, n_idle, max_idle);
    }

    ObjType* _active_one_object() 
    {
        lock_guard<mutex> lock(mtx);
        ObjType* obj = oc_idle.front(); 
        oc_idle.pop_front();
        oc_active.push_back(obj);
        --n_idle;
        ++ n_actived;
        return obj;
    }

    ObjType* _create_one_object() 
    {
        lock_guard<mutex> lock(mtx);
        ObjType* obj = factory->create();
        if(obj) n_actived++;
        oc_active.push_back(obj);
        return obj;
    }

    void _destroy_one_object(ObjType* obj) {
        if(!obj) return;
        factory->destroy(obj);
        n_actived--;
    }

     void _deactive_one_object(ObjType* obj) {
        if(!obj) return;
        oc_active.remove(obj);
        oc_idle.push_back(obj);
        n_actived--;
        n_idle++;
    }

    // 在该对象被退还给对象池之前调用
    virtual void _hook_return_object(OT* obj) {
        if(!obj) return;
        obj->dec_count();
    }

    // 在该对象从对象池中获取出来时调用
    virtual void _hook_request_object(OT* obj) {
        if(!obj) return;
        obj->inc_count();
    }

    // 获取对象
    ObjType* request_object() 
    {
        ObjType* obj = nullptr;
        lock_guard<mutex> lock(mtx);

        // 有空闲可用的对象，且被激活的对象数没达到上限
        if(n_idle > 0 && n_actived < max_actived) {
            obj = _active_one_object();
        }

        // 没有空闲可用的对象，且被激活的对象数没有到上限，创建一个新对象
        if(n_actived < max_actived) {
            obj = _create_one_object();
        } 
        
        // 成功获取对象
        if(obj) {
            _hook_request_object(obj);
            printd("request_object: %p\n", obj);
        }

        // 返回对象，无法成功获取对象时返回 nullptr
        return obj; 
    }

    // 退还对象
    void return_object(ObjType* obj) 
    {
        if(!obj) return;
        printd("return_object: %p\n", obj);
        _hook_return_object(obj);

        lock_guard<std::mutex> lock(mtx);
        
        // 该对象需要释放
        if(n_idle >= max_idle) {
            _destroy_one_object(obj);
        } 
        // 该对象需要重新返回到对象池中
        else _deactive_one_object(obj);
    }
};

