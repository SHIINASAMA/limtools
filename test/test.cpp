#include <stdio.h>
#include "io/Console.hpp"

int main()
{
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
}
