#include "FixedThreadPool.hpp"

FixedThreadPool *FixedThreadPool::pool = nullptr;

FixedThreadPool::FixedThreadPool(int threadNum)
{
    this->threadNum = threadNum;
    threads = new std::thread[threadNum];
    for (int i = 0; i < threadNum; i++)
    {
        threads[i] = std::thread(std::bind(&FixedThreadPool::Run, this, i));
    }
}

void FixedThreadPool::CreateFixedThreadPool(int threadNum)
{
    if (FixedThreadPool::pool == nullptr)
    {
        FixedThreadPool::pool = new FixedThreadPool(threadNum);
    }
}

FixedThreadPool *FixedThreadPool::GetFixedThreadPool()
{
    return FixedThreadPool::pool;
}

void FixedThreadPool::Start()
{
    command = Commands::RUN;
}

void FixedThreadPool::Pause()
{
    command = Commands::STOP;
}

//设置命令后等待线程悉数退出后回收资源
void FixedThreadPool::Exit()
{
    command = Commands::EXIT;
    for (int i = 0; i < threadNum; i++)
    {
        threads[i].join();
    }
    delete[] threads;
}

void FixedThreadPool::AddTask(Task *task)
{
    __mutex.lock();
    __tasks.push(task);
    __mutex.unlock();
}

void FixedThreadPool::Run(int id)
{
restart:
    switch (command)
    {
    case Commands::RUN:
    {
        if (__tasks.size() != 0)
        {
            Task *task;
            __mutex.lock();
            task = __tasks.front();
            __tasks.pop();
            __mutex.unlock();
            printf("线程%d收到任务\n", id);
            task->Run();
        }
        else
        {
            _sleep(1000);
        }
        goto restart;
    }
    case Commands::STOP:
    {
        _sleep(1000);
        goto restart;
    }
    case Commands::EXIT:
    {
        break;
    }
    }
}

FixedThreadPool::~FixedThreadPool()
{
    Exit();
}