#include <stdio.h>
#include "io/Console.hpp"

int main()
{
    Console::Write("Hello ,%d\n", 10);
    Console::Write("Hi,%s%c,%b\n", "Worl", 'd', 20);
}
