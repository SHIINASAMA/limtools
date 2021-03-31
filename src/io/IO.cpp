/**
 * @file IO.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief IO句柄管理类定义（Windows only）
 * @version 0.1
 * @date 2021-03-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifdef _WIN32
#include "IO.hpp"

IO *IO::io = new IO();

IO::IO()
{
    this->inputHandle = GetStdHandle(STD_INPUT_HANDLE);
    this->outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

IO::~IO()
{
    CloseHandle(this->inputHandle);
    CloseHandle(this->outputHandle);
}

HANDLE IO::GetInputHandle()
{
    return io->inputHandle;
}

HANDLE IO::GetOutputHandle()
{
    return io->outputHandle;
}
#endif