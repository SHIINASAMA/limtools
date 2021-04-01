/**
 * @file ThreadGroup.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 线程组类声明
 * @version 0.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _THREADGROUP_HPP_
#define _THREADGROUP_HPP_

#include "SafeThread.hpp"

/**
 * @brief 线程组
 * 
 */
class ThreadGroup
{
protected:
    std::mutex mutex;

public:
    /**
     * @brief 初始化线程组
     * 
     */
    ThreadGroup();

    /**
     * @brief 将一个线程添加至线程组内
     * 
     * @param thread 目标线程
     */
    void Add(SafeThread *thread);
};

#endif