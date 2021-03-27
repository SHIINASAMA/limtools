#include "ThreadGroup.hpp"

ThreadGroup::ThreadGroup()
{
}

void ThreadGroup::Add(SafeThread *thread)
{
    thread->SetMutex(&this->mutex);
}