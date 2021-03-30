#ifdef _WIN32
#include <Windows.h>
#define ID HANDLE
#elif __linux__
#define ID int
#endif

/**
 * @brief 访问模式
 * 
 */
enum class AccessMode
{
#ifdef _WIN32
    READ,
    WRITE,
    BOTH
#elif __linux__
    READ,
    WRITE,
    BOTH
#endif
};

/**
 * @brief 打开模式
 * 
 */
enum class OpenMode
{
#ifdef _WIN32
    /**
     * @brief 文件存在则报错
     * 
     */
    NEW = CREATE_NEW,
    /**
     * @brief 文件存在则打开，不存在则创建
     * 
     */
    CREATE = OPEN_ALWAYS,
    /**
     * @brief 打开文件，不存在则报错
     * 
     */
    OPEN = OPEN_EXISTING,
#elif __linux__
    /**
     * @brief 文件存在则报错
     * 
     */
    NEW,
    /**
     * @brief 文件存在则截断，不存在则创建
     * 
     */
    CREATE,
    /**
     * @brief 打开文件，不存在则报错
     * 
     */
    OPEN
#endif
};

/**
 * @brief Seek定位位置
 * 
 */
enum class SeekPos
{
#ifdef _WIN32
    /**
     * @brief 文件开头
     * 
     */
    BEGIN = FILE_BEGIN,
    /**
     * @brief 文件尾部
     * 
     */
    END = FILE_END,
#elif __linux__
#endif
};

class File
{
protected:
    ID id;

    virtual ~File();

public:
    File();

    bool Open(char *path, AccessMode accessMode, OpenMode openMode);

    int Write(void *buf, int len);

    int Read(void *buf, int len);

    void SetOffset(long pos);

    void SetOffset(SeekPos pos);

    void Close();
};