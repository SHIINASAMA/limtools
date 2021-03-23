/**
 * @file Console.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 控制台类定义
 * @version 0.1
 * @date 2021-03-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Console.hpp"

#ifdef _WIN32
#include "IO.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#elif __linux__
#endif

void Console::Put(char *str)
{
#ifdef _WIN32
    DWORD len;
    WriteConsole(IO::GetOutputHandle(),
                 str,
                 strlen(str),
                 &len,
                 NULL);
#elif __linux__
#endif
}

void Console::Put(char ch)
{
#ifdef _WIN32
    DWORD len;
    WriteConsole(IO::GetOutputHandle(),
                 &ch,
                 1,
                 &len,
                 NULL);
#elif __linux__
#endif
}

void Console::Put(long l, int radix)
{
    char str[32];
    ltoa(l, str, radix);
    Put(str);
}

// void Console::Put(unsigned long l, int radix)
// {
//     char str[32];
//     ultoa(l, str, radix);
//     Put(str);
// }

void Console::Put(double d)
{
    char str[32];
    sprintf(str, "%lf", d);
    Put(str);
}

void Console::Write(const char *str, ...)
{
    va_list args;
    va_start(args, str);
    while (*str)
    {
        char ch = *str;
        if (ch == '%')
        {
            switch (*(++str))
            {
            case '%': //百分号
            {
                Put('%');
                str++;
                break;
            }
            case 's': //字符串
            {
                char *str = va_arg(args, char *);
                Put(str);
                str++;
                break;
            }
            case 'd': //十进制整型
            {
                long l = va_arg(args, long);
                Put(l, 10);
                str++;
                break;
            }
            case 'x': //十六进制整型
            {
                long l = va_arg(args, long);
                Put(l, 16);
                str++;
                break;
            }
            case 'o': //八进制整型
            {
                long l = va_arg(args, long);
                Put(l, 8);
                str++;
                break;
            }
            case 'b': //二进制整型
            {
                long l = va_arg(args, long);
                Put(l, 2);
                str++;
                break;
            }
            case 'c': //字符
            {
                char ch = va_arg(args, int);
                Put(ch);
                str++;
                break;
            }
            case 'f': //浮点型
            {
                double d = va_arg(args, double);
                Put(d);
                str++;
                break;
            }
            }
        }
        else
        {
            Put(ch);
            str++;
        }
        va_end(args);
    }
}