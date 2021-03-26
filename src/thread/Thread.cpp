/**
 * @file Thread.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 线程类定义
 * @version 0.1
 * @date 2021-03-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Thread.hpp"

Thread::Thread()
{
}

Thread::~Thread()
{
    if (this->worker.joinable())
    {
        this->worker.join();
    }
}

void Thread::Start()
{
    this->worker = std::thread(std::bind(&Thread::Run, this));
}

std::thread::id Thread::GetId()
{
    return this->worker.get_id();
}

void Thread::Join()
{
    if (this->worker.joinable())
    {
        this->worker.join();
    }
}

void Thread::Detach()
{
    this->worker.detach();
}