/**
 * @file Task.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 任务基类定义
 * @version 0.1
 * @date 2021-03-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Task.hpp"

void Task::SetArgs(void *args) {
    this->args = args;
}