#include "threadpool.hpp"

///////////////////////////////////////////////////////////////////////////////
// Test

int add(int x1, int x2) { return x1 + x2; }
int sum(int x1, int x2, int x3) { return x1 + x2 + x3; }

int main() {
    // 2 work threads
    MyThreadPool executor(2);
    // results array
    vector<future<int>> res;

    // commit some tasks
    for(int i = 0; i < 5; i++) {
        auto r1 = executor.commit(add, i, i);
        auto r2 = executor.commit(sum, i, i, i);
        res.push_back(move(r1));
        res.push_back(move(r2));
    }

    // wait for task finished
    for(auto& r: res) {
        COUT(r.get());
    }

    puts("finished");
}
