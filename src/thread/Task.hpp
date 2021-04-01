/**
 * @file Task.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 任务基类声明
 * @version 0.1
 * @date 2021-03-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _TASK_HPP_
#define _TASK_HPP_

/**
 * @brief 任务类
 * 
 */
class Task
{
protected:
    void *args = nullptr;

public:
    /**
     * @brief 任务过程（需要重写）
     * 
     */
    virtual void Run() = 0;

    /**
     * @brief 设置任务参数
     * 
     * @param args 
     */
    void SetArgs(void *args);
};

#endif