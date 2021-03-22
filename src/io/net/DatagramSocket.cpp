/**
 * @file DatagramSocket.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief UDP套接字定义
 * @version 0.1
 * @date 2021-03-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "DatagramSocket.hpp"

DatagramSocket::DatagramSocket(SocketMode mode, char *ipaddr, unsigned short port)
    : Socket()
{
    this->sock = ::socket(AF_INET, SOCK_DGRAM, 0);
    this->sin.sin_family = AF_INET;
#ifdef _WIN32
    this->sin.sin_addr.S_un.S_addr = inet_addr(ipaddr);
#elif __linux__
    this->sin.sin_addr.s_addr = inet_addr(ipaddr);
#endif
    this->sin.sin_port = htons(port);
    if (mode == SocketMode::Server)
    {
        bind(this->sock, (sockaddr *)&this->sin, sizeof(sockaddr));
    }
}

int DatagramSocket::Write(char *buffer, int size)
{
    return sendto(this->sock, buffer, size, 0, (sockaddr *)&this->sin, sizeof(sockaddr));
}

int DatagramSocket::Read(char *buffer, int size)
{
#ifdef _WIN32
    int len = sizeof(sockaddr);
#elif __linux__
    socklen_t len = sizeof(sockaddr);
#endif
    return recvfrom(this->sock, buffer, size, 0, (sockaddr *)&this->sin, &len);
}

int DatagramSocket::Close()
{
    return Socket::Close();
}