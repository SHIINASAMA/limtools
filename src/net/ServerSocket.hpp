/**
 * @file ServerSocket.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief TCP套接字服务端声明
 * @version 0.1
 * @date 2021-03-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SERVERSOCKET_HPP_
#define _SERVERSOCKET_HPP_

#include "Socket.hpp"

/**
 * @brief Socket服务端
 * 
 */
class ServerSocket : public Socket {
public:
    /**
     * @brief Socket服务端初始化
     * 
     * @param port 监听端口
     * @param backlog 队列上限
     */
    ServerSocket(unsigned short port, int backlog);
};

#endif