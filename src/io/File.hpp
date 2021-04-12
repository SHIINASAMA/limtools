/**
 * @file File.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 文件IO类声明
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _FILE_HPP_
#define _FILE_HPP_

#ifdef _WIN32

#include <Windows.h>

#define ID HANDLE
#elif __linux__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define ID int
#endif

/**
 * @brief 访问模式
 * 
 */
enum class AccessMode
{
#ifdef _WIN32
    READ,
    WRITE,
    BOTH
#elif __linux__
    READ = O_RDONLY,
    WRITE = O_WRONLY,
    BOTH = O_RDWR
#endif
};

/**
 * @brief 打开模式
 * 
 */
enum class OpenMode
{
#ifdef _WIN32
    /**
     * @brief 文件存在则报错
     * 
     */
    NEW = CREATE_NEW,
    /**
     * @brief 文件存在则截断，不存在则创建
     * 
     */
    CREATE = CREATE_ALWAYS,
    /**
     * @brief 打开文件，不存在则报错
     * 
     */
    OPEN = OPEN_EXISTING,
#elif __linux__
    /**
     * @brief 文件存在则报错
     * 
     */
    NEW = O_CREAT | O_EXCL,
    /**
     * @brief 文件存在则截断，不存在则创建
     * 
     */
    CREATE = O_CREAT | O_TRUNC,
    /**
     * @brief 打开文件，不存在则报错
     * 
     */
    OPEN
#endif
};

/**
 * @brief Seek定位位置
 * 
 */
enum class SeekPos
{
#ifdef _WIN32
    /**
     * @brief 文件开头
     * 
     */
    BEGIN = FILE_BEGIN,
    /**
     * @brief 文件尾部
     * 
     */
    END = FILE_END,
#elif __linux__
    /**
     * @brief 文件开头
     * 
     */
    BEGIN = SEEK_SET,
    /**
     * @brief 文件尾部
     * 
     */
    END = SEEK_END
#endif
};

/**
 * @brief 文件类
 * 
 */
class File
{
protected:
#ifdef _WIN32
    ID id = INVALID_HANDLE_VALUE;
#elif __linux__
    ID id = -1;
#endif


public:
    /**
     * @brief 初始化一个文件操作对象
     * 
     */
    File();

    /**
     * @brief 销毁对象
     * 
     */
    virtual ~File();

    /**
     * @brief 打开一个文件
     * 
     * @param path 文件路径
     * @param accessMode 访问模式
     * @param openMode 打开模式
     * @return true 打开成功
     * @return false 打开失败
     */
    bool Open(const char *path, AccessMode accessMode, OpenMode openMode);

    /**
     * @brief 向文件写入数据
     * 
     * @param buf 缓存
     * @param len 写入大小
     * @return int 实际写入缓存大小
     */
    int Write(void *buf, int len);

    /**
     * @brief 从文件中读取数据
     * 
     * @param buf 缓存
     * @param len 读取大小
     * @return int 实际读取大小
     */
    int Read(void *buf, int len);

    /**
     * @brief 设置偏移位置
     * 
     * @param pos 偏移大小
     */
    void SetOffset(long pos);

    /**
     * @brief 设置基准位置
     * 
     * @param pos 基准位置
     */
    void SetOffset(SeekPos pos);

    /**
     * @brief 以当前节点为基准移动位置
     * 
     * @param pos 偏移大小
     */
    void MoveOffset(long pos);

    /**
     * @brief 获取当前位置
     *
     * @return Offset
     */
    long GetOffset();

    /**
     * @brief 关闭当前连接
     * 
     */
    void Close();

    /**
     * @brief 获取文件长度
     *
     * @return 文件长度
     */
    long GetFileLength();
};

#endif