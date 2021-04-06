#include "net/http/Request.hpp"
#include "io/Console.hpp"

int main()
{
    Request *require = new Request("/", "220.181.38.148\0", 80);
    require->SetArg("Host", "www.baidu.com");
    auto request = require->Get();
    for (auto itor = request->recvMap.begin(); itor != request->recvMap.end(); itor++)
    {
        Console::Write("%s: %s\n", itor->first, itor->second);
    }

    Console::Print(request->content);

    return 0;
}