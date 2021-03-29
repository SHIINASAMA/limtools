/**
 * @file FixedThreadPool.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 不可变线程池定义
 * @version 0.1
 * @date 2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "FixedThreadPool.hpp"

FixedThreadPool *FixedThreadPool::pool = nullptr;

FixedThreadPool::FixedThreadPool(short threadNum)
{
    this->threadNum = threadNum;
    threads = new std::thread[threadNum];
    for (short i = 0; i < threadNum; i++)
    {
        threads[i] = std::thread(std::bind(&FixedThreadPool::RunTask, this, i));
    }
}

void FixedThreadPool::CreateFixedThreadPool(short threadNum, bool hasRes)
{
    if (FixedThreadPool::pool == nullptr)
    {
        FixedThreadPool::pool = new FixedThreadPool(threadNum);
        ::hasRes = hasRes;
    }
}

FixedThreadPool *FixedThreadPool::GetFixedThreadPool()
{
    return FixedThreadPool::pool;
}

FixedThreadPool::~FixedThreadPool()
{
}

void FixedThreadPool::Run()
{
    command = Commands::RUN;
}

void FixedThreadPool::Stop()
{
    command = Commands::STOP;
}

void FixedThreadPool::Exit()
{
    command = Commands::EXIT;
    for (int i = 0; i < threadNum; i++)
    {
        threads[i].join();
    }
    delete[] threads;
}

void FixedThreadPool::RunTask(short threadId)
{
restart:
    switch (command)
    {
    case Commands::RUN:
    {
        mutex1.lock();
        if (taskList.size() != 0)
        {
            Task *task = taskList.front();
            taskList.pop();
            mutex1.unlock();

            //printf("线程%d执行中...\n", threadId);
            if (hasRes)
            {
                mutex2.lock();
                completeList.push(task);
                mutex2.unlock();
            }
        }
        else
        {
            mutex1.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        goto restart;
    }
    case Commands::STOP:
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        goto restart;
    }
    case Commands::EXIT:
    {
        break;
    }
    }
}

short FixedThreadPool::GetThreadTotal()
{
    return this->threadNum;
}

short FixedThreadPool::GetAliveThreadNum()
{
    return aliveThreadNum;
}

Task *FixedThreadPool::Pop()
{
    mutex2.lock();
    if (completeList.size() != 0)
    {
        Task *temp = completeList.front();
        completeList.pop();
    }
    else
    {
        mutex2.unlock();
        return nullptr;
    }
    return nullptr;
}

void FixedThreadPool::Push(Task *task)
{
    mutex1.lock();
    taskList.push(task);
    mutex1.unlock();
}