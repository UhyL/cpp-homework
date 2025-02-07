#ifndef SEMAPHORE_H
#define SEMAPHORE_H

// Task 3
#include <condition_variable>
#include <mutex>
class Semaphore {
    // TODO: Task3
private:
    int count;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Semaphore(int init_count) : count(init_count) {};

    void P() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return count > 0; });
        --count;
    }

    void V() {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        cv.notify_all();
    }
};

#endif // SEMAPHORE_H

/*
在C++20标准中，C++引入了信号量的机制。但现在就由你来实现信号量PV操作。

在Task3中，你需要编写Semaphore.h和Semaphore.cpp，利用互斥锁和条件变量来实现一个信号量类。你需要实现的函数有：

带一个整数类型参数count的构造函数，count表示信号量的初始值。
P()函数，意义同操作系统课程。
V()函数，意义同操作系统课程。
你可以参考单元测试来实现你的信号量类。完成Task3，您可以获得所有的分数
*/