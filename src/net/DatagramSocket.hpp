/**
 * @file DatagramSocket.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief UDP套接字声明
 * @version 0.1
 * @date 2021-03-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _DATAGRAMSOCKET_HPP_
#define _DATAGRAMSOCKET_HPP_

#include "Socket.hpp"

/**
 * @brief UDP套接字
 * 
 */
class DatagramSocket : Socket {
public:
    /**
     * @brief UDP套接字初始化
     * 
     * @param mode 连接模式
     * @param ipaddr 目标IP
     * @param port 目标端口
     */
    DatagramSocket(SocketMode mode, const char *ipaddr, unsigned short port);

    /**
     * @brief 写入数据
     * 
     * @param buffer 数据缓存
     * @param size 数据块大小
     * @return int 实际写入数据块大小
     */
    int Write(char *buffer, int size);

    /**
     * @brief 读取数据
     * 
     * @param buffer 数据缓存
     * @param size 数据块大小
     * @return int 实际读取数据块大小
     */
    int Read(char *buffer, int size);

    /**
     * @brief 断开连接
     * 
     * @return int 成功返回0，失败返回非零
     */
    int Close();
};

#endif