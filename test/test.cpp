#include "io/Console.hpp"
#include "net/Socket.hpp"

int main()
{
    char *buf[8];
    int count = Socket::GetHostByName(buf, 8, "www.baidu.com");
    if (count <= 0)
    {
        Console::WriteColorful("error\n", Console::Colors::Red);
    }
    else
    {
        Console::Write("获取到%d个IP\n", count);
        for (int i = 0; i < count; i++)
        {
            Console::Write("IP Address %d:%s\n", i, buf[i]);
        }
    }

    return 0;
}