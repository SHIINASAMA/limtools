/**
 * @file SafeThread.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 安全的线程类声明
 * @version 0.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SAFETHREAD_HPP_
#define _SAFETHREAD_HPP_

#include "Thread.hpp"
#include <mutex>

/**
 * @brief 安全线程
 * 
 */
class SafeThread : public Thread
{
protected:
    std::mutex *mutex = nullptr;

public:
    /**
     * @brief 设置互斥量，可以手动设置，但推荐使用ThreadGroup管理
     * 
     * @param mutex 
     */
    void SetMutex(std::mutex *mutex);

    /**
     * @brief 详情参照 std::mutex::lock()
     * 
     */
    void Lock();

    /**
     * @brief 详情参照 std::mutex::unlock()
     * 
     */
    void Unlock();

    /**
     * @brief 详情参照 std::mutex::try_lock()
     * 
     */
    bool TryLock();

    /**
     * @brief 启动安全线程
     * 
     */
    void Start() override;
};

#endif