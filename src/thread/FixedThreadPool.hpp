#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include "Task.hpp"

/**
 * @brief 线程命令枚举
 * 
 */
enum class Commands
{
    /**
     * @brief 暂停执行
     * 
     */
    STOP,
    /**
     * @brief 继续执行
     * 
     */
    RUN,
    /**
     * @brief 终止执行
     * 
     */
    EXIT
};

static volatile Commands command = Commands::STOP;

static std::mutex mutex1;

static std::mutex mutex2;

static std::queue<Task *> taskList;

static std::queue<Task *> completeList;

static volatile short aliveThreadNum = 0;

static bool hasRes = false;

/**
 * @brief 不可变线程池
 * 
 */
class FixedThreadPool
{
protected:
    int threadNum = 0;

    std::thread *threads;

    FixedThreadPool(short threadNum);

    static FixedThreadPool *pool;

    ~FixedThreadPool();

    void RunTask(short threadId);

public:
    static void CreateFixedThreadPool(short threadNum, bool hasRes = true);

    static FixedThreadPool *GetFixedThreadPool();

    void Run();

    void Stop();

    void Exit();

    short GetThreadTotal();

    short GetAliveThreadNum();

    Task *Pop();

    void Push(Task *task);
};