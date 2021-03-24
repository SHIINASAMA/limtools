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

void Console::Print(const char *str)
{
#ifdef _WIN32
    DWORD len;
    WriteConsole(IO::GetOutputHandle(), str, strlen(str), &len, NULL);
#elif __linux__
    write(0, str, strlen(str));
#endif
}

void Console::FormatWrite(char *buf, const char *fmt, va_list args)
{
    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            switch (*fmt)
            {
            case '%':
            {
                *buf = '%';
                buf++;
                fmt++;
                break;
            }
            case 'b':
            {
                char temp[33];
                long l = va_arg(args, long);
                ltoa(l, temp, 2);
                int len = strlen(temp);
                strcpy(buf, temp);
                buf += len;
                fmt++;
                break;
            }
            case 'o':
            {
                char temp[33];
                long l = va_arg(args, long);
                ltoa(l, temp, 8);
                int len = strlen(temp);
                strcpy(buf, temp);
                buf += len;
                fmt++;
                break;
            }
            case 'd':
            {
                char temp[33];
                long l = va_arg(args, long);
                ltoa(l, temp, 10);
                int len = strlen(temp);
                strcpy(buf, temp);
                buf += len;
                fmt++;
                break;
            }
            case 'x':
            {
                char temp[33];
                long l = va_arg(args, long);
                ltoa(l, temp, 16);
                int len = strlen(temp);
                strcpy(buf, temp);
                buf += len;
                fmt++;
                break;
            }
            case 'f':
            {
                char temp[33];
                double d = va_arg(args, double);
                sprintf(temp, "%lf", d);
                int len = strlen(temp);
                strcpy(buf, temp);
                buf += len;
                fmt++;
                break;
            }
            case 's':
            {
                char *temp = va_arg(args, char *);
                int len = strlen(temp);
                strcpy(buf, temp);
                buf += len;
                fmt++;
                break;
            }
            case 'c':
            {
                int temp = va_arg(args, int);
                *buf = (char)temp;
                buf++;
                fmt++;
                break;
            }
            }
        }
        else
        {
            *buf = *fmt;
            buf++;
            fmt++;
        }
    }
}

void Console::Write(const char *fmt, ...)
{
    char temp[1024];
    va_list args;
    va_start(args, fmt);
    FormatWrite(temp, fmt, args);
    va_end(args);
    Print(temp);
}