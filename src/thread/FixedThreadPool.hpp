#include <queue>
#include <mutex>
#include "Task.hpp"

class FixedThreadPool
{
protected:
    bool isRun = false;

    int threadNum = 0;

    //队列互斥量
    std::mutex mutex;

    //任务队列
    std::queue<Task *> tasks;

    FixedThreadPool(int threadNum);

public:
    static void CreateFixedThreadPool(int threadNum);

    static FixedThreadPool *GetFixedThreadPool();

    void Start();

    void Pause();

    bool AddTask();
};