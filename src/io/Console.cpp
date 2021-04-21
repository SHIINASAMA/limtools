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

#ifdef __linux__
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
        //__set_errno(EDOM);
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

void Console::Print(const char *str) {
#ifdef _WIN32
    DWORD len;
    WriteConsole(IO::GetOutputHandle(), str, strlen(str), &len, NULL);
#elif __linux__
    write(1, str, strlen(str));
#endif
}

void Console::FormatWrite(char *buf, const char *fmt, va_list args) {
    // while (*fmt)
    // {
    //     if (*fmt == '%')
    //     {
    //         fmt++;ws
    //         switch (*fmt)
    //         {
    //         case '%':
    //         {
    //             *buf = '%';
    //             buf++;
    //             fmt++;
    //             break;
    //         }
    //         case 'b':
    //         {
    //             char temp[33];
    //             long l = va_arg(args, long);
    //             ltoa(l, temp, 2);
    //             int len = strlen(temp);
    //             strcpy(buf, temp);
    //             buf += len;
    //             fmt++;
    //             break;
    //         }
    //         case 'o':
    //         {
    //             char temp[33];
    //             long l = va_arg(args, long);
    //             ltoa(l, temp, 8);
    //             int len = strlen(temp);
    //             strcpy(buf, temp);
    //             buf += len;
    //             fmt++;
    //             break;
    //         }
    //         case 'd':
    //         {
    //             char temp[33];
    //             long l = va_arg(args, long);
    //             ltoa(l, temp, 10);
    //             int len = strlen(temp);
    //             strcpy(buf, temp);
    //             buf += len;
    //             fmt++;
    //             break;
    //         }
    //         case 'x':
    //         {
    //             char temp[33];
    //             long l = va_arg(args, long);
    //             ltoa(l, temp, 16);
    //             int len = strlen(temp);
    //             strcpy(buf, temp);
    //             buf += len;
    //             fmt++;
    //             break;
    //         }
    //         case 'f':
    //         {
    //             char temp[33];
    //             double d = va_arg(args, double);
    //             sprintf(temp, "%lf", d);
    //             int len = strlen(temp);
    //             strcpy(buf, temp);
    //             buf += len;
    //             fmt++;
    //             break;
    //         }
    //         case 's':
    //         {
    //             char *temp = va_arg(args, char *);
    //             int len = strlen(temp);
    //             strcpy(buf, temp);
    //             buf += len;
    //             fmt++;
    //             break;
    //         }
    //         case 'c':
    //         {
    //             int temp = va_arg(args, int);
    //             *buf = (char)temp;
    //             buf++;
    //             fmt++;
    //             break;
    //         }
    //         }
    //     }
    //     else
    //     {
    //         *buf = *fmt;
    //         buf++;
    //         fmt++;
    //     }
    // }
    // *buf = '\0';

    const char *header = fmt;
    char *nbuf = buf;
    int len = 0;
    while (*header) {
        if (*header != '%') {
            len++;
            header++;
        }
        else if (*header) {
            memcpy(nbuf, fmt, len);
            nbuf += len;
            fmt += len + 1;
            len = 0;
            switch (*fmt) {
                case '%': {
                    *nbuf = '%';
                    nbuf++;
                    fmt++;
                    header += 2;
                    break;
                }
                case 'b': {
                    char temp[33];
                    long l = va_arg(args, long);
                    ltoa(l, temp, 2);
                    int len = strlen(temp);
#ifdef _WIN32
                    strcpy_s(nbuf, strlen(temp) + 1, temp);
#elif __linux__
                    strcpy(nbuf, temp);
#endif
                    nbuf += len;
                    fmt++;
                    header += 2;
                    break;
                }
                case 'o': {
                    char temp[33];
                    long l = va_arg(args, long);
                    ltoa(l, temp, 8);
                    int len = strlen(temp);
#ifdef _WIN32
                    strcpy_s(nbuf, strlen(temp) + 1, temp);
#elif __linux__
                    strcpy(nbuf, temp);
#endif
                    nbuf += len;
                    fmt++;
                    header += 2;
                    break;
                }
                case 'd': {
                    char temp[33];
                    long l = va_arg(args, long);
                    ltoa(l, temp, 10);
                    int len = strlen(temp);
#ifdef _WIN32
                    strcpy_s(nbuf, strlen(temp) + 1, temp);
#elif __linux__
                    strcpy(nbuf, temp);
#endif
                    nbuf += len;
                    fmt++;
                    header += 2;
                    break;
                }
                case 'x': {
                    char temp[33];
                    long l = va_arg(args, long);
                    ltoa(l, temp, 16);
                    int len = strlen(temp);
#ifdef _WIN32
                    strcpy_s(nbuf, strlen(temp) + 1, temp);
#elif __linux__
                    strcpy(nbuf, temp);
#endif
                    nbuf += len;
                    fmt++;
                    header += 2;
                    break;
                }
                case 'f': {
                    char temp[33];
                    double d = va_arg(args, double);
                    sprintf(temp, "%lf", d);
                    int len = strlen(temp);
#ifdef _WIN32
                    strcpy_s(nbuf, strlen(temp) + 1, temp);
#elif __linux__
                    strcpy(nbuf, temp);
#endif
                    nbuf += len;
                    fmt++;
                    header += 2;
                    break;
                }
                case 's': {
                    char *temp = va_arg(args, char *);
                    int len = strlen(temp);
#ifdef _WIN32
                    strcpy_s(nbuf, strlen(temp) + 1, temp);
#elif __linux__
                    strcpy(nbuf, temp);
#endif
                    nbuf += len;
                    fmt++;
                    header += 2;
                    break;
                }
                case 'c': {
                    int temp = va_arg(args, int);
                    *nbuf = (char) temp;
                    nbuf++;
                    fmt++;
                    header += 2;
                    break;
                }
            }
        }
    }
    memcpy(nbuf, fmt, len);
    nbuf += len;
    *nbuf = '\0';
}

void Console::Format(char *buf, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    FormatWrite(buf, fmt, args);
    va_end(args);
}

void Console::Write(const char *fmt, ...) {
    char temp[1024];
    va_list args;
    va_start(args, fmt);
    FormatWrite(temp, fmt, args);
    va_end(args);
    Print(temp);
}

void Console::Read(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vscanf(fmt, args);
    va_end(args);
}

void Console::Put(long l, int radix) {
    char temp[33];
    ltoa(l, temp, radix);
    Print(temp);
}

void Console::Put(double d) {
    char temp[33];
    sprintf(temp, "%lf", d);
    Print(temp);
}

void Console::Put(char c) {
    char temp[2]{c, '\0'};
    Print(temp);
}

void Console::NewLine() {
    Print("\n");
}

void Console::SetColor(Colors fontColor) {
#ifdef _WIN32
    SetConsoleTextAttribute(IO::GetOutputHandle(), (WORD) fontColor);
#elif __linux__
    char font[3];
    ltoa((long)fontColor, font, 10);
    font[2] = '\0';
    Write("\033[%sm", font);
#endif
}

void Console::SetColor(Colors fontColor, Colors bkColor) {
#ifdef _WIN32
    SetConsoleTextAttribute(IO::GetOutputHandle(), (WORD) bkColor * 0x10 | (WORD) fontColor);
#elif __linux__
    char bk[3];
    ltoa((long)bkColor + 10, bk, 10);
    bk[2] = '\0';
    char font[3];
    ltoa((long)fontColor, font, 10);
    font[2] = '\0';
    Write("\033[%s;%sm", bk, font);
#endif
}

void Console::ClearColor() {
#ifdef _WIN32
    SetConsoleTextAttribute(IO::GetOutputHandle(), (WORD) Colors::White);
#elif __linux__
    Print("\033[0m");
#endif
}

void Console::WriteColorful(const char *str, Colors fontColor) {
#ifdef _WIN32
    SetColor(fontColor);
    Print(str);
    ClearColor();
#elif __linux__
    char font[3];
    ltoa((long)fontColor, font, 10);
    font[2] = '\0';
    Write("\033[%sm%s\033[0m", font, str);
#endif
}

void Console::WriteColorful(const char *str, Colors fontColor, Colors bkColor) {
#ifdef _WIN32
    SetColor(fontColor, bkColor);
    Print(str);
    ClearColor();
#elif __linux__
    char bk[3];
    ltoa((long)bkColor + 10, bk, 10);
    bk[2] = '\0';
    char font[3];
    ltoa((long)fontColor, font, 10);
    font[2] = '\0';
    Write("\033[%s;%sm%s\033[0m", bk, font, str);
#endif
}