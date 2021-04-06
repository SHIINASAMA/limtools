/**
 * @file Request.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 请求类声明
 * @version 0.1
 * @date 2021-04-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "Response.hpp"
#include "../Socket.hpp"
#include <cstdio>
#include <string>
#include <string.h>

/**
 * @brief 请求类
 * 
 */
class Request
{
private:
    std::string send_args;
    Response *response = nullptr;
    char url[1024]{0};
    char ipaddr[16]{0};
    int port = 80;

public:
    /**
     * @brief 初始化一个请求对象
     * 
     * @param url 目标url
     * @param ipaddr 目标ip地址
     * @param port 目标端口
     */
    Request(const char *url, const char *ipaddr, unsigned short port);

    /**
     * @brief 释放资源
     * 
     */
    ~Request();

    /**
     * @brief Get请求
     * 
     * @return Response* 响应对象
     */
    Response *Get();

    /**
     * @brief 设置参数
     * 
     * @param key 键
     * @param value 值
     */
    void SetArg(const char *key, const char *value);
};
