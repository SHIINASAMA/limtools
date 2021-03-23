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

#include "IO.hpp"

HANDLE IO::inputHandle;
HANDLE IO::outputHandle;

IO::IO(){
    inputHandle = GetStdHandle(STD_INPUT_HANDLE);
    outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

IO::~IO(){
    CloseHandle(inputHandle);
    CloseHandle(outputHandle);
}

HANDLE IO::GetInputHandle(){
    return inputHandle;
}

HANDLE IO::GetOutputHandle(){
    return outputHandle;
}