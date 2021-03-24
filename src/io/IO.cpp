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

HANDLE IO::inputHandle;
HANDLE IO::outputHandle;

HANDLE IO::GetInputHandle(){
    if(inputHandle == NULL){
        inputHandle = GetStdHandle(STD_INPUT_HANDLE);
    }
    return inputHandle;
}

HANDLE IO::GetOutputHandle(){
    if(outputHandle == NULL){
        outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    return outputHandle;
}
#endif