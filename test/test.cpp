#define test_colorful
#include <stdio.h>
#include "io/Console.hpp"

int main()
{
#ifdef test_print
    Console::Write("Hello ,%d\n", 10);
    Console::Write("Hi,%s%c,%b\n", "Worl", 'd', 20);

    long i;
    Console::Read("%d", &i);
    Console::Put(i);

    double d = 3.14f;
    Console::Put(d);

    char c = 'C';
    Console::Put(c);

    return 0;
#endif

#ifdef test_colorful
    using Colors = Console::Colors;
    Colors fontColor = Colors::Red;
    Colors bkColor = Colors::Blue;
    Console::WriteColorful("Hello", fontColor, bkColor);
    return 0;
#endif

}
