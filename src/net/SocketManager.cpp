/**
 * @file SocketManager.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 负责在 Windows 下进行初始化管理的专有类（Windows only）
 * @version 0.1
 * @date 2021-04-14
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "SocketManager.hpp"

int SocketManager::StatusCode = -1;

SocketManager::SocketManager()
{
    if (StatusCode == 0)
    {
        return;
    }

    WSADATA wsaData;
    StatusCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
}

SocketManager::~SocketManager()
{
    if(StatusCode != 0){
        return;
    }

    WSACleanup();
    StatusCode = 0;
}

