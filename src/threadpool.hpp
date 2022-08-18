// 静态线程池的简单实现

#include "base.h"

#include <functional>
#include <stdexcept>
#include <sstream>

// 获取线程ID
auto get_tid() {
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    std::string stid = oss.str();
    unsigned long long tid = std::stoull(stid);
    return tid;
}

void sleep_ms(int ms) {
    if(ms <= 0) ms = 10;
    auto time = chrono::milliseconds(ms);
    this_thread::sleep_for(time);
}

class MyThreadPool 
{
private:
    using Task = packaged_task<void()>; // 定义类型
    vector<thread> pool;                // 工作线程队列
    deque<Task> tasks;                  // 任务队列（可选 ThreadSafeQueue）
    atomic_bool is_running = true;      // 运行状态
    atomic_int nwaiting = 0;            // 空闲线程数
    atomic_int nworking = 0;            // 工作中的线程数
    mutex lock;                         // 同步
    condition_variable cv;              // 条件阻塞
    // 统计信息
    int ntask = 0; // 任务数

public: // API
    // 线程池初始化，默认创建 2 个工作线程。
    MyThreadPool(unsigned int size);

    // 销毁线程池，释放所有相关资源。
    ~MyThreadPool();

    // 向线程池提交一个任务
    template <typename F, typename... Args>
    auto commit(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>;

    // 动态管理工作线程数量
    void add_worker();
    void del_worker();

    // 执行任务前后的回调
    void hook_before_work();
    void hook_after_work();

    // 获取状态信息
    auto get_worker_number() {
        return pool.size();    
    }

};

///////////////////////////////////////////////////////////////////////////////
// Impl

MyThreadPool::MyThreadPool(unsigned int size = 2) 
{ 
    for(unsigned int i = 0; i < size; i++) {
        add_worker();
    }
}

// 销毁线程池，释放所有相关资源
MyThreadPool::~MyThreadPool() 
{
    puts("MyThreadPool is closing...");
    is_running = false;
    cv.notify_all();

    for(auto& t : pool) {
        if(t.joinable()) t.join();
    }

    printd("===SUMMARY===\n");
    printd("finished task number: %d\n", ntask - (int) tasks.size());
}

template <typename F, typename... Args>
auto MyThreadPool::commit(F&& f, Args&&... args)
  -> future<typename result_of<F(Args...)>::type> 
{
    // 定义任务返回值类型
    using task_return_type = typename result_of<F(Args...)>::type;

    // 创建内部任务
    auto task = packaged_task<task_return_type()>(
    bind(forward<F>(f), forward<Args>(args)...));
    auto result = task.get_future();
    
    if(!is_running) {
        puts("ThreadPool is not running!");
        return result;
    }

    unique_lock<mutex> lk(lock);
    tasks.emplace_back(move(task));

    // 通知工作线程
    cv.notify_one();

    printd("task submited\n");
    ntask++;
    return result;
}

void MyThreadPool::hook_before_work() 
{
    printd("task ready: %s : tid = %lld\n", __func__, get_tid());
    nwaiting--;
    nworking++;
}

void MyThreadPool::hook_after_work() 
{
    printd("task finished: %s : tid = %lld\n", __func__, get_tid());
    nwaiting++;
    nworking--; 
}

void MyThreadPool::add_worker() 
{
    if(pool.size() >= 8) return;
    nwaiting++;

    pool.emplace_back([this] () {
        while(is_running) {
            if(!is_running) { return; }

            // double check for tasks number
            if(tasks.size() == 0) {
                puts("waiting tasks for 3s...");
                sleep_ms(3000);
                if (tasks.size() == 0) {
                    puts("worker go home...");
                    return;
                }
            }

            Task task;
            {
                unique_lock<mutex> lk(lock); 
                cv.wait(lk, [this] { return !tasks.empty(); });
                task = move(tasks.front());  
                tasks.pop_front();
                printd("get task: %s : tid = %lld\n", __func__, get_tid());
            }

            hook_before_work();
            task();  // Run the task
            hook_after_work();
        }
    } );
}

void MyThreadPool::del_worker() {
    // todo
}
