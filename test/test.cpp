#include "io/Console.hpp"
#include "thread/FixedThreadPool.hpp"

volatile long i = 0;

class MyTask : public Task
{
public:
    bool done = false;
    virtual void Run() override
    {
        //Console::Write("任务被执行\n");
#ifdef _WIN32
        _sleep(1000);
#elif __linux__
        sleep(1);
#endif
        done = true;
    }
};

int main()
{
    FixedThreadPool::CreateFixedThreadPool(100, false);
    auto pool = FixedThreadPool::GetFixedThreadPool();
    pool->Run();
    MyTask *tasks = new MyTask[1000];
    for (int i = 0; i < 1000; i++)
    {
        pool->Push(&tasks[i]);
    }

#ifdef _WIN32
    _sleep(5000);
#elif __linux__
    sleep(5);
#endif
    pool->Exit();
    Console::Write("线程池已关闭\n");
    return 0;
}
