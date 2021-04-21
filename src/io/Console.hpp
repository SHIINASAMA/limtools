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

#ifndef _CONSOLE_HPP_
#define _CONSOLE_HPP_

#ifdef _WIN32

#include "IO.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define ltoa(value, buf, radix) _ltoa_s(value, buf, 32, radix)
#elif __linux__
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define ltoa _ltoa
#endif

/**
 * @brief 控制台库
 * 
 */
class Console {
private:
    static void FormatWrite(char *buf, const char *fmt, va_list args);

public:
    /**
     * @brief 静态输出，不存在变量时请使用这个
     * 
     * @param str 目标字符串
     */
    static void Print(const char *str);

    /**
     * @brief 格式化字符串
     * 
     * @param buf 字符缓存
     * @param fmt 目标格式
     * @param ... 参数
     */
    static void Format(char *buf, const char *fmt, ...);

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

    /**
     * @brief 输出换行
     * 
     */
    static void NewLine();

    /**
     * @brief 颜色枚举
     * 
     */
    enum class Colors {
#ifdef _WIN32
        Black = 0x0,
        Blue = 0x1,
        Green = 0x2,
        LightGreen = 0x3,
        Red = 0x4,
        Purple = 0x5,
        Yellow = 0x6,
        White = 0x7,
        Grey = 0x8,
        PaleBlue = 0x9,
        PaleGreen = 0xA,
        PaleLightGreen = 0xB,
        PaleRed = 0xC,
        PalePurple = 0xD,
        PaleYellow = 0xE,
        LightWhite = 0xF
#elif __linux__
        Black = 30,
        Red = 31,
        Green = 32,
        Yellow = 33,
        Blue = 34,
        Purple = 35,
        Azure = 36,
        White = 37
#endif
    };

    /**
     * @brief 设置颜色
     * 
     * @param fontColor 前景色
     */
    static void SetColor(Colors fontColor);

    /**
     * @brief 设置颜色
     * 
     * @param fontColor 前景色 
     * @param bkColor 背景色
     */
    static void SetColor(Colors fontColor, Colors bkColor);

    /**
     * @brief 清除颜色
     * 
     */
    static void ClearColor();

    /**
     * @brief 彩色输出
     * @param str 目标字符串
     * @param fontColor 前景色
     */
    static void WriteColorful(const char *str, Colors fontColor);

    /**
     * @brief 彩色输出
     * 
     * @param str 目标字符串
     * @param fontColor 前景色
     * @param bkColor 背景色
     */
    static void WriteColorful(const char *str, Colors fontColor, Colors bkColor);
};

#endif