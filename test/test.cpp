#include "io/Console.hpp"
#include "thread/ThreadGroup.hpp"

volatile long i = 0;

class MyThread : public SafeThread
{
    void Run() override
    {
        for (int n = 0; n < 100000; n++)
        {
            this->Lock();
            i++;
            this->Unlock();
        }
    }
};

int main()
{
    ThreadGroup group;
    MyThread th1, th2;
    group.Add(&th1);
    group.Add(&th2);

    th1.Start();
    th2.Start();

    th1.Join();
    th2.Join();

    Console::Put(i);
    Console::NewLine();
    return 0;
}
