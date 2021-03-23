/**
 * @file ServerSocket.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief TCP套接字服务端定义
 * @version 0.1
 * @date 2021-03-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ServerSocket.hpp"

ServerSocket::ServerSocket(unsigned short port, int backlog)
    : Socket(SocketMode::Server, (char*)"0.0.0.0", port)
{
    this->Listen(backlog);
}