#include "net/Socket.hpp"
#include "io/Console.hpp"

int main()
{
    char *buf[1];
    int count = Socket::GetHostByName(buf, 1, "www.baidu.com");
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