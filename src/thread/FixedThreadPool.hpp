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

static std::mutex __mutex;

static std::queue<Task *> __tasks;

class FixedThreadPool
{
protected:
    int threadNum = 0;

    std::thread *threads;

    FixedThreadPool(int threadNum);

    static FixedThreadPool *pool;

    ~FixedThreadPool();

    void Run(int id);

public:
    static void CreateFixedThreadPool(int threadNum);

    static FixedThreadPool *GetFixedThreadPool();

    void Start();

    void Pause();

    void Exit();

    void AddTask(Task *task);
};