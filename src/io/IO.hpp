/**
 * @file IO.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief IO句柄管理类声明（Windows only）
 * @version 0.1
 * @date 2021-03-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _IO_HPP_
#define _IO_HPP_

#ifdef _WIN32
#include <Windows.h>

/**
 * @brief IO句柄管理类
 * 
 */
class IO
{

private:
    HANDLE inputHandle;
    HANDLE outputHandle;

    static IO *io;

    IO();

    ~IO();
public:
    /**
     * @brief 获取输入句柄
     * 
     * @return HANDLE 输入句柄
     */
    static HANDLE GetInputHandle();

    /**
     * @brief 获取输出句柄
     * 
     * @return HANDLE 输出句柄
     */
    static HANDLE GetOutputHandle();
};
#endif

#endif