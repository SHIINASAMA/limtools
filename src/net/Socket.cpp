/**
 * @file Socket.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief TCP套接字定义
 * @version 0.1
 * @date 2021-03-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Socket.hpp"

#ifdef _WIN32

SocketManager* Socket::manager = new SocketManager();

Socket::Socket()
{
}

Socket::Socket(SocketMode mode, const char *ipaddr, unsigned short port)
{
    this->sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->sin.sin_family = AF_INET;
    this->sin.sin_addr.s_addr = inet_addr(ipaddr);
    this->sin.sin_port = htons(port);

    if (mode == SocketMode::Server)
    {
        bind(this->sock, (SOCKADDR *) &this->sin, sizeof(SOCKADDR));
    }
}

int Socket::Listen(int backlog)
{
    return listen(this->sock, backlog);
}

Socket::~Socket()
{
    this->Close();
}

int Socket::Read(char *buffer, int size)
{
    return recv(this->sock, buffer, size, NULL);
}

int Socket::Write(const char *buffer, int size)
{
    return send(this->sock, buffer, size, NULL);
}

Socket Socket::Accept()
{
    Socket res;
    int len = sizeof(SOCKADDR);
    res.sock = accept(this->sock, (SOCKADDR *) &res.sin, &len);
    return res;
}

int Socket::Connect()
{
    return connect(this->sock, (SOCKADDR *) &this->sin, sizeof(SOCKADDR));
}

int Socket::Shutdown(ShutdownMode mode)
{
    return shutdown(this->sock, (int) mode);
}

int Socket::Close()
{
    return closesocket(this->sock);
}

int Socket::GetHostByName(char *buf[], int size, const char *domain)
{
    Socket sock;
    auto hosts = gethostbyname(domain);
    if (hosts == nullptr)
    {
        return -1;
    }

    if (hosts->h_addrtype == AF_INET6)
    {
        return -2;
    }

    int count = 0;
    for (char *pt = hosts->h_addr_list[0]; pt != NULL; pt = hosts->h_addr_list[++count])
    {
        if (count < size)
        {
            in_addr in{};
            in.S_un.S_addr = *(u_long *) pt;
            buf[count] = inet_ntoa(in);
        }
        else
        {
            break;
        }
    }

    return count;
}

#endif

#ifdef __linux__
Socket::Socket()
{
}

Socket::Socket(SocketMode mode,const char *ipaddr, unsigned short port)
{
    this->sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->sin.sin_family = AF_INET;
    this->sin.sin_addr.s_addr = inet_addr(ipaddr);
    this->sin.sin_port = htons(port);

    if (mode == SocketMode::Server)
    {
        bind(this->sock, (sockaddr *)&this->sin, sizeof(sockaddr));
    }
}

Socket::~Socket()
{
    this->Close();
}

Socket Socket::Accept()
{
    Socket res;
    socklen_t len = sizeof(sockaddr);
    res.sock = accept(this->sock, (sockaddr *)&res.sin, &len);
    return res;
}

int Socket::Listen(int backlog)
{
    return listen(this->sock, backlog);
}

int Socket::Connect()
{
    return connect(this->sock, (sockaddr *)&this->sin, sizeof(sockaddr));
}

int Socket::Read(char *buffer, int size)
{
    return read(this->sock, buffer, size);
}

int Socket::Write(const char *buffer, int size)
{
    return write(this->sock, buffer, size);
}

int Socket::Shutdown(ShutdownMode mode)
{
    return shutdown(this->sock, (int)mode);
}

int Socket::Close()
{
    return close(this->sock);
}

int Socket::GetHostByName(char *buf[], int size, const char* domain) {
    auto hosts = gethostbyname(domain);
    if (hosts == nullptr)
    {
        return -1;
    }

    if (hosts->h_addrtype == AF_INET6)
    {
        return -2;
    }

    int count = 0;
    for (char *pt = hosts->h_addr_list[0]; pt != NULL; pt = hosts->h_addr_list[++count])
    {
        if (count < size)
        {
            in_addr in;
            in.s_addr = *(u_long *)pt;
            buf[count] = inet_ntoa(in);
        }
        else
        {
            break;
        }
    }

    return count;
}

#endif
