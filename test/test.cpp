#include "net/http/Request.hpp"
#include "io/Console.hpp"

int main()
{
    Request *get = new Request("/", "220.181.38.148", 80);
    get->SetArg("Host", "www.baidu.com");
    auto res1 = get->Get();
    for (auto itor = res1->Args.begin(); itor != res1->Args.end(); itor++)
    {
        Console::Write("%s: %s\n", itor->first, itor->second);
    }
    Console::Print(res1->Content);
    delete get;

    // Console::NewLine();

    // Request *post = new Request("/", "112.80.248.75\0", 80);
    // post->SetArg("Host", "www.baidu.com");
    // post->SetArg("Content-Lenght", "5");
    // auto res2 = post->Post("Hello", 5);
    // for (auto itor = res2->recvMap.begin(); itor != res2->recvMap.end(); itor++)
    // {
    //     Console::Write("%s: %s\n", itor->first, itor->second);
    // }
    // Console::Print(res2->content);
    // int len = strlen(res2->content);
    // delete post;

    return 0;
}