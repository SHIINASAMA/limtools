/**
 * @file ThreadGroup.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 线程组定义
 * @version 0.1
 * @date 2021-04-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ThreadGroup.hpp"

ThreadGroup::ThreadGroup()
{
}

void ThreadGroup::Add(SafeThread *thread)
{
    thread->SetMutex(&this->mutex);
}