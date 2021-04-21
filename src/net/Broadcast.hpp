/**
 * @file Broadcast.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 广播类声明
 * @version 0.1
 * @date 2021-03-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _BROADCAST_HPP_
#define _BROADCAST_HPP_

#include "Socket.hpp"

/**
 * @brief 广播类
 * 
 */
class Broadcast : Socket {
public:
    /**
     * @brief 初始化广播类
     * 
     * @param mode 连接模式
     * @param port 目标端口
     */
    Broadcast(SocketMode mode, unsigned short port);

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