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
    static void Print(const char *str);

    static void FormatWrite(char *buf, const char *fmt, va_list args);

    static void Write(const char *fmt, ...);
};
