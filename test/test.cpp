#include "io/Console.hpp"
#include "thread/Thread.hpp"

class MyThread : public Thread
{
    void Run() override
    {
        Console::Print("Child:我是子线程\n");
    }
};

int main()
{
    MyThread th;
    th.Start();
    th.Join();
    Console::Print("Main:子线程执行完毕");
    return 0;
}
