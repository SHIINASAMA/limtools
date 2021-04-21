/**
 * @file Broadcast.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 广播类定义
 * @version 0.1
 * @date 2021-03-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Broadcast.hpp"

Broadcast::Broadcast(SocketMode mode, unsigned short port) : Socket() {
    this->sock = ::socket(AF_INET, SOCK_DGRAM, 0);
    this->sin.sin_family = AF_INET;
    this->sin.sin_port = htons(port);

    if (mode == SocketMode::Server) {
#ifdef _WIN32
        this->sin.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
#elif __linux__
        this->sin.sin_addr.s_addr = htonl(INADDR_BROADCAST);
#endif
        bool bOpt = true;
        setsockopt(this->sock, SOL_SOCKET, SO_BROADCAST, (char *) &bOpt, sizeof(bOpt));
    }
    else {
#ifdef _WIN32
        this->sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
#elif __linux__
        this->sin.sin_addr.s_addr = htonl(INADDR_ANY);
#endif
        bind(this->sock, (sockaddr *) &this->sin, sizeof(sockaddr));
    }
}

int Broadcast::Write(char *buffer, int size) {
    return sendto(this->sock, buffer, size, 0, (sockaddr *) &this->sin, sizeof(sockaddr));
}

int Broadcast::Read(char *buffer, int size) {
#ifdef _WIN32
    int len = sizeof(sockaddr);
#elif __linux__
    socklen_t len = sizeof(sockaddr);
#endif
    return recvfrom(this->sock, buffer, size, 0, (sockaddr *) &this->sin, &len);
}

int Broadcast::Close() {
    return Socket::Close();
}