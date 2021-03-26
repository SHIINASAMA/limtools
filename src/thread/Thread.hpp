/**
 * @file Thread.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 线程类声明
 * @version 0.1
 * @date 2021-03-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <thread>

/**
 * @brief 线程类
 * 
 */
class Thread
{
private:
    std::thread worker;


public:
    /**
     * @brief 初始化线程类
     * 
     */
    Thread();

    /**
     * @brief 析构函数
     * 
     */
    virtual ~Thread();

    /**
     * @brief 启动线程，将会调用Thread::Run函数
     * 
     */
    void Start();

    /**
     * @brief 获取线程ID
     * 
     * @return std::thread::id 线程ID 
     */
    std::thread::id GetId();

    /**
     * @brief Join该线程
     * @attention 详情参照c++11 thread::join()
     */
    void Join();

    /**
     * @brief Detach该线程
     * @attention 详情参照c++11 thread::detach()
     * 
     */
    void Detach();

    /**
     * @brief 当调用Thread::Start时会由子线程来执行该函数
     * @attention 需要重写
     */
    virtual void Run() = 0;
};