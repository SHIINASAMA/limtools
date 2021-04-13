#include "net/Socket.hpp"
#include "io/Console.hpp"

int main()
{
    Console::Write("Hello\n");
    auto socket = new Socket(SocketMode::Server,"0.0.0.0",9090);
    socket->Listen(15);
    auto client = socket->Accept();
    client.Close();
    socket->Close();
    return 0;
}