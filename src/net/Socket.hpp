/**
 * @file Socket.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief TCP套接字声明
 * @version 0.1
 * @date 2021-03-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_

/**
 * @brief 连接模式
 * 
 */
enum class SocketMode {
    /**
     * @brief 作为服务端
     * 
     */
    Server,
    /**
     * @brief 作为客户端
     * 
     */
    Client
};

/**
 * @brief 断开模式
 * 
 */
enum class ShutdownMode {
    /**
     * @brief 断开读
     * 
     */
    Read,
    /**
     * @brief 断开写
     * 
     */
    Write,
    /**
     * @brief 两者都断开
     * 
     */
    Both
};

#ifdef _WIN32

#include "SocketManager.hpp"

/**
 * @brief 套接字类
 * 
 */
class Socket {
private:
    static SocketManager *manager;

protected:
    SOCKET sock;
    SOCKADDR_IN sin;

public:
    Socket();

    /**
     * @brief 初始化套接字
     * 
     * @param mode 连接模式
     * @param ipaddr 目标IP
     * @param port 目标端口
     */
    Socket(SocketMode mode, const char *ipaddr, unsigned short port);

    /**
     * @brief 销毁套接字
     *
     */
    ~Socket();

    /**
     * @brief 等待连接后返回客户端套接字
     * 
     * @return Socket 客户端套接字
     */
    Socket Accept();

    /**
     * @brief 设置监听队列上限
     * 
     * @param backlog 上限
     * @return int 实际上限
     */
    int Listen(int backlog);

    /**
     * @brief 连接
     * 
     * @return int 连接成功返回0，非零则失败 
     */
    int Connect();

    /**
     * @brief 写入数据
     * 
     * @param buffer 数据缓存
     * @param size 数据块大小
     * @return int 实际写入数据块大小
     */
    int Write(const char *buffer, int size);

    /**
     * @brief 读取数据
     * 
     * @param buffer 数据缓存
     * @param size 数据块大小
     * @return int 实际读取数据块大小
     */
    int Read(char *buffer, int size);

    /**
     * @brief 已某种方式断开连接
     * 
     * @param mode 断开模式
     * @return int 成功返回0，失败返回非零
     */
    int Shutdown(ShutdownMode mode);

    /**
     * @brief 断开连接
     * 
     * @return int 成功返回0，失败返回非零
     */
    int Close();

    /**
     * @brief 域名解析
     * 
     * @param buf 缓存
     * @param size 读取IP数量上限
     * @param domain 目标域名
     * @return 返回的IP数量
     */
    static int GetHostByName(char *buf[], int size, const char *domain);
};

#endif

#ifdef __linux__
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
class Socket
{
protected:
    int sock;
    sockaddr_in sin{0};

public:
    /**
     * @brief 初始化套接字
     */
    Socket();

    /**
     * @brief 销毁套接字
     *
     */
    ~Socket();

    /**
     * @brief 初始化套接字
     * 
     * @param mode 连接模式
     * @param ipaddr 目标IP
     * @param port 目标端口
     */
    Socket(SocketMode mode,const char *ipaddr, unsigned short port);

    /**
     * @brief 等待连接后返回客户端套接字
     * 
     * @return Socket 客户端套接字
     */
    Socket Accept();

    /**
     * @brief 连接
     * 
     * @return int 连接成功返回0，非零则失败 
     */
    int Listen(int backlog);

    /**
     * @brief 连接
     * 
     * @return int 连接成功返回0，非零则失败 
     */
    int Connect();

    /**
     * @brief 写入数据
     * 
     * @param buffer 数据缓存
     * @param size 数据块大小
     * @return int 实际写入数据块大小
     */
    int Write(const char *buffer, int size);

    /**
     * @brief 读取数据
     * 
     * @param buffer 数据缓存
     * @param size 数据块大小
     * @return int 实际读取数据块大小
     */
    int Read(char *buffer, int size);

    /**
     * @brief 已某种方式断开连接
     * 
     * @param mode 断开模式
     * @return int 成功返回0，失败返回非零
     */
    int Shutdown(ShutdownMode mode);

    /**
     * @brief 断开连接
     * 
     * @return int 成功返回0，失败返回非零
     */
    int Close();

    /**
     * @brief 域名解析
     * 
     * @param buf 缓存
     * @param size 缓存大小
     * @param domain 目标域名
     *
     * @return 返回的IP数量
     */
    static int GetHostByName(char *buf[], int size, const char *domain);
};
#endif

#endif
