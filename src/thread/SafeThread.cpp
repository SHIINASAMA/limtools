#include "SafeThread.hpp"

void SafeThread::SetMutex(std::mutex *mutex) {
    if (this->mutex == nullptr) {
        this->mutex = mutex;
    }
}

void SafeThread::Lock() {
    this->mutex->lock();
}

void SafeThread::Unlock() {
    this->mutex->unlock();
}

bool SafeThread::TryLock() {
    return this->mutex->try_lock();
}

void SafeThread::Start() {
    if (this->mutex != nullptr) {
        this->worker = std::thread(std::bind(&SafeThread::Run, this));
    }
}