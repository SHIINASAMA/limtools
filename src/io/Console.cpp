#include "Console.hpp"
#include "IO.hpp"

void Console::Put(char *str)
{
    DWORD len;
    WriteConsole(IO::GetOutputHandle(),
                 str,
                 strlen(str),
                 &len,
                 NULL);
}

void Console::Write(char* str,...){
    Put(str);
}