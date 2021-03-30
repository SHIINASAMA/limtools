#include "File.hpp"

File::File()
{
}

File::~File()
{
#ifdef _WIN32
    if (this->id != INVALID_HANDLE_VALUE)
    {
        Close();
    }
#elif __linux__
    if (this->id != -1)
    {
        Close();
    }
#endif
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
    if (openMode == OpenMode::NEW)
    {
        int temp = open(path, (int)accessMode | (int)openMode, S_IRWXU);
        if (temp != -1)
        {
            this->id = temp;
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (openMode == OpenMode::CREATE)
    {
        if (access(path, F_OK) == 0)
        {
            int temp = open(path, (int)accessMode | O_TRUNC, S_IRWXU);
            if (temp != -1)
            {
                this->id = temp;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            int temp = open(path, (int)accessMode | O_CREAT, S_IRWXU);
            if (temp != -1)
            {
                this->id = temp;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        if (access(path, F_OK) == 0)
        {
            int temp = open(path, (int)accessMode, S_IRWXU);
            if (temp != -1)
            {
                this->id = temp;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
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
    return write(this->id, buf, len);
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
    return read(this->id, buf, len);
#endif
}

void File::SetOffset(long pos)
{
#ifdef _WIN32
    SetFilePointer(this->id, pos, 0, 0);
#elif __linux__
    lseek(this->id, pos, SEEK_SET);
#endif
}

void File::SetOffset(SeekPos pos)
{
#ifdef _WIN32
    SetFilePointer(this->id, 0, 0, (DWORD)pos);
#elif __linux__
    lseek(this->id, 0, (int)pos);
#endif
}

void File::MoveOffset(long pos)
{
#ifdef _WIN32

#elif __linux__
    lseek(this->id, pos, SEEK_CUR);
#endif
}

void File::Close()
{
#ifdef _WIN32
    CloseHandle(this->id);
    this->id = -1;
#elif __linux__
    close(this->id);
    this->id = -1;
#endif
}