#include "io/Console.hpp"
#include "io/File.hpp"

int main()
{
    auto file = new File();
    if (false == file->Open((char *)"a.txt", AccessMode::BOTH, OpenMode::CREATE))
    {
        Console::Write("Open file failed!");
    }
    else
    {
        char *wbuf = (char *)"Hello中国あいうえお\0";
        int wlen = file->Write(wbuf, strlen(wbuf));
        char rbuf[128]{0};
        file->SetOffset(0);
        int rlen = file->Read(rbuf, 128);
        Console::Write("Written %d bytes\nRead:%s(%d bytes)\n", wlen, rbuf, rlen);
        file->Close();
    }
    return 0;
}
