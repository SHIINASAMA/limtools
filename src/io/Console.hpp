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
char *ltoa(long value, char *string, int radix)
{
    char tmp[33];
    char *tp = tmp;
    long i;
    unsigned long v;
    int sign;
    char *sp;

    if (radix > 36 || radix <= 1)
    {
        __set_errno(EDOM);
        return 0;
    }

    sign = (radix == 10 && value < 0);
    if (sign)
        v = -value;
    else
        v = (unsigned long)value;
    while (v || tp == tmp)
    {
        i = v % radix;
        v = v / radix;
        if (i < 10)
            *tp++ = i + '0';
        else
            *tp++ = i + 'a' - 10;
    }

    if (string == 0)
        string = (char *)malloc((tp - tmp) + sign + 1);
    sp = string;

    if (sign)
        *sp++ = '-';
    while (tp > tmp)
        *sp++ = *--tp;
    *sp = 0;
    return string;
}
#endif


/**
 * @brief 控制台库
 * 
 */
class Console
{
public:
    static void Print(const char *str);

    static void FormatWrite(char *buf, const char *fmt, va_list args);

    static void Write(const char *fmt, ...);
};
