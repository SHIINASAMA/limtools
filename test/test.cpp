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
        _sleep(1000);
        done = true;
    }
};

int main()
{
    FixedThreadPool::CreateFixedThreadPool(1000, false);
    auto pool = FixedThreadPool::GetFixedThreadPool();
    pool->Run();
    MyTask *tasks = new MyTask[3000];
    for (int i = 0; i < 3000; i++)
    {
        pool->Push(&tasks[i]);
    }

    _sleep(5000);
    pool->Exit();
    Console::Write("线程池已关闭\n");
    return 0;
}
