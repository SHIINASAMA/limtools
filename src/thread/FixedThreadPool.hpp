/**
 * @file FixedThreadPool.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 不可变线程池声明
 * @version 0.1
 * @date 2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _FIXEDTHREADPOOL_HPP_
#define _FIXEDTHREADPOOL_HPP_

#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include "Task.hpp"

/**
 * @brief 线程命令枚举
 * 
 */
enum class Commands {
    /**
     * @brief 暂停执行
     * 
     */
    STOP,
    /**
     * @brief 继续执行
     * 
     */
    RUN,
    /**
     * @brief 终止执行
     * 
     */
    EXIT
};

static volatile Commands command = Commands::STOP;

static std::mutex mutex1;

static std::mutex mutex2;

static std::queue<Task *> taskList;

static std::queue<Task *> completeList;

static volatile short aliveThreadNum = 0;

static bool hasRes = false;

/**
 * @brief 不可变线程池
 * 
 */
class FixedThreadPool {
protected:
    int threadNum = 0;

    std::thread *threads;

    FixedThreadPool(short threadNum);

    static FixedThreadPool *pool;

    ~FixedThreadPool();

    void RunTask(short threadId);

public:
    /**
     * @brief 创建不可变线程池的单例
     * 
     * @param threadNum 线程池中的线程数量
     * @param hasRes 处理完成的任务是否需要添加至 completeList
     */
    static void CreateFixedThreadPool(short threadNum, bool hasRes = true);

    /**
     * @brief 获取不可变线程池单例
     * 
     * @return FixedThreadPool* 不可变线程池
     */
    static FixedThreadPool *GetFixedThreadPool();

    /**
     * @brief 启动线程池
     * 
     */
    void Run();

    /**
     * @brief 暂停线程池
     * 
     */
    void Stop();

    /**
     * @brief 结束线程池并释放资源
     * 
     */
    void Exit();

    /**
     * @brief 获取线程池当前的线程总数
     * 
     * @return short 线程数量
     */
    short GetThreadTotal();

    /**
     * @brief 获取线程池中活跃的线程总数
     * 
     * @return short 
     */
    short GetAliveThreadNum();

    /**
     * @brief 从 completeList 取出一个任务
     * 
     * @return Task* 已完成的任务，队列为空则返回 nullptr
     */
    Task *Pop();

    /**
     * @brief 将任务放入队列中
     * 
     * @param task 目标任务
     */
    void Push(Task *task);
};

#endif