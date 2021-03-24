/**
 * @file Console.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 控制台库声明
 * @version 0.1
 * @date 2021-03-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifdef _WIN32
#include "IO.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#elif __linux__
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#endif

/**
 * @brief 控制台库
 * 
 */
class Console
{
public:
    /**
     * @brief 静态输出，不存在变量时请使用这个
     * 
     * @param str 目标字符串
     */
    static void Print(const char *str);

    /**
     * @brief 构造格式字符串
     * 
     * @param buf 结果缓存
     * @param fmt 目标格式
     * @param args 参数
     */
    static void FormatWrite(char *buf, const char *fmt, va_list args);

    /**
     * @brief 格式化输出
     * 
     * @param fmt 目标格式
     * @param ... 参数
     */
    static void Write(const char *fmt, ...);

    /**
     * @brief scanf弱化版，仅用于与Write对应，对某些功能有要求请使用scanf，否则应该对应风格
     * 
     * @param fmt 目标格式
     * @param ... 参数
     */
    static void Read(const char *fmt, ...);

    /**
     * @brief 输出整型
     * 
     * @param l 目标整型
     * @param radix 目标进制
     */
    static void Put(long l, int radix = 10);

    /**
     * @brief 输出浮点数
     * 
     * @param d 目标浮点数
     */
    static void Put(double d);

    /**
     * @brief 输出字符
     * 
     * @param c 目标字符
     */
    static void Put(char c);
};
