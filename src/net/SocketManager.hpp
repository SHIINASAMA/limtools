/**
 * @file SocketManager.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 负责在 Windows 下进行初始化管理的专有类（Windows only）
 * @version 0.1
 * @date 2021-04-14
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _SOCKETMANAGER_HPP_
#define _SOCKETMANAGER_HPP_

#ifdef _WIN32

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * @brief 负责在 Windows 下进行初始化管理的专有类
 */
class SocketManager {
public:
    /**
     * @brief 网络模块初始化状态码
     */
    static int StatusCode;

    /**
     * @brief 网络模块初始化
     */
    SocketManager();

    /**
     * @brief 释放资源
     */
    ~SocketManager();
};

#endif

#endif
