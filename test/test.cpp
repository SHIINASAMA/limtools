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
    FixedThreadPool::CreateFixedThreadPool(20);
    auto pool = FixedThreadPool::GetFixedThreadPool();
    pool->Start();
    MyTask *tasks = new MyTask[100];
    for (int i = 0; i < 100; i++)
    {
        pool->AddTask(&tasks[i]);
    }

    _sleep(15000);
    auto b = tasks[99].done;
    pool->Exit();
    Console::Write("线程池已关闭\n");
    return 0;
}
