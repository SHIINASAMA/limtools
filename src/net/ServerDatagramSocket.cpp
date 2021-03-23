/**
 * @file ServerDatagramSocket.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 广播服务端定义
 * @version 0.1
 * @date 2021-03-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ServerDatagramSocket.hpp"

ServerDatagramSocket::ServerDatagramSocket(unsigned short port)
    : DatagramSocket(SocketMode::Server, (char*)"0.0.0.0", port)
{
}