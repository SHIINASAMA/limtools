#include "File.hpp"

File::File()
{
}

File::~File()
{
    Close();
}

bool File::Open(char *path, AccessMode accessMode, OpenMode openMode)
{
#ifdef _WIN32
    DWORD l;
    if (accessMode == AccessMode::READ)
    {
        l = GENERIC_READ;
    }
    else if (accessMode == AccessMode::WRITE)
    {
        l = GENERIC_WRITE;
    }
    else
    {
        l = GENERIC_WRITE | GENERIC_READ;
    }

    ID temp = CreateFile(path, l, NULL, NULL, (DWORD)openMode, FILE_ATTRIBUTE_NORMAL, NULL);
    if (temp != INVALID_HANDLE_VALUE)
    {
        this->id = temp;
        return true;
    }
    else
    {
        return false;
    }
#elif __linux__
#endif
}

int File::Write(void *buf, int len)
{
#ifdef _WIN32
    DWORD writtenLen;
    if (WriteFile(this->id, buf, len, &writtenLen, NULL))
    {
        return (int)writtenLen;
    }
    else
    {
        return -1;
    }
#elif __linux__
#endif
}

int File::Read(void *buf, int len)
{
#ifdef _WIN32
    DWORD readLen;
    if (ReadFile(this->id, buf, len, &readLen, NULL))
    {
        return (int)readLen;
    }
    else
    {
        return -1;
    }
#elif __linux__
#endif
}

void File::Seek(long pos)
{
#ifdef _WIN32
    SetFilePointer(this->id, 0, 0, pos);
#elif __linux__
#endif
}

void File::Close()
{
#ifdef _WIN32
    CloseHandle(this->id);
#elif __linux__
#endif
}