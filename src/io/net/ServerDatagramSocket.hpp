/**
 * @file ServerDatagramSocket.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 广播服务端声明
 * @version 0.1
 * @date 2021-03-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "DatagramSocket.hpp"

/**
 * @brief 广播服务端
 * 
 */
class ServerDatagramSocket : public DatagramSocket
{
public:
    /**
     * @brief 初始化广播服务端类
     * 
     * @param port 目标端口
     */
    ServerDatagramSocket(unsigned short port);
};