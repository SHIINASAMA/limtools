#include "io/File.hpp"
#include "io/Console.hpp"

int main()
{
    File *file = new File();
    auto res = file->Open("E:\\Code\\limtools\\LICENSE",AccessMode::BOTH,OpenMode::OPEN);
    // auto error = GetLastError();
    long length = file->GetFileLength();
    file->Close();
    return 0;
}