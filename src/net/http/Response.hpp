/**
 * @file Response.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 响应类声明
 * @version 0.1
 * @date 2021-04-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <map>
#include <stdio.h>
#include <string.h>

/**
 * @brief 忽略字符串大小写的比较函数
 * 
 */
struct ucmp {
    bool operator()(const char *pc1, const char *pc2) const {
#ifdef _WIN32
        return _stricmp(pc1, pc2) < 0;
#elif __linux__
        return strcasecmp(pc1, pc2) < 0;
#endif
    }
};

/**
 * @brief 响应类
 * 
 */
class Response {
public:
    /**
     * @brief 初始化一个响应对象
     * 
     */
    Response();

    /**
     * @brief 释放资源
     * 
     */
    ~Response();

    /**
     * @brief 响应参数Map
     * 
     */
    std::map<char *, char *, ucmp> Args;

    /**
     * @brief Http响应状态码
     * 
     */
    unsigned short StatusCode = 0;

    /**
     * @brief 响应内容
     * 
     */
    char *Content = nullptr;

    /**
     * @brief 响应内容长度
     * 
     */
    int ContentLength = 0;
};
