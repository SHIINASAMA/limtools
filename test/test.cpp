#include "net/http/Request.hpp"
#include "io/Console.hpp"

int main()
{
    char *temp[1];
    if (Socket::GetHostByName(temp, 1, "www.baidu.com") <= 0)
    {
        Console::Print("域名解析失败\n");
        return -1;
    }

    const char *ipaddr = temp[0];

    Request *get = new Request("/", ipaddr, 80);
    get->SetArg("Host", "www.baidu.com");
    auto res1 = get->Get();
    for (auto itor = res1->Args.begin(); itor != res1->Args.end(); itor++)
    {
        Console::Write("%s: %s\n", itor->first, itor->second);
    }
    Console::Write("%d == %d\n", res1->ContentLength, strlen(res1->Content));
    delete get;

    Console::NewLine();

    Request *post = new Request("/", ipaddr, 80);
    post->SetArg("Host", "www.baidu.com");
    post->SetArg("Content-Lenght", "5");
    auto res2 = post->Post("Hello", 5);
    for (auto itor = res2->Args.begin(); itor != res2->Args.end(); itor++)
    {
        Console::Write("%s: %s\n", itor->first, itor->second);
    }
    Console::Write("%d == %d\n", res2->ContentLength, strlen(res2->Content));
    delete post;

    return 0;
}