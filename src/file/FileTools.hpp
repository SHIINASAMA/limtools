/**
 * @file FileTools.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 文件解析杂项函数
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <string.h>

/**
 * @brief 用于在std::map中提供char*之间的比较方式 
 */
struct cmp
{
    bool operator()(const char *pc1, const char *pc2) const
    {
        return strcmp(pc1, pc2) < 0;
    }
};