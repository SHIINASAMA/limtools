/**
 * @file Response.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 响应类定义
 * @version 0.1
 * @date 2021-04-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Response.hpp"

Response::Response()
{
}

Response::~Response()
{
    if (this->ContentLength != 0)
    {
        delete[] this->Content;
    }

    if (this->Args.size() != 0)
    {
        for (auto itor = this->Args.begin(); itor != this->Args.end(); itor++)
        {
            delete [] itor->first;
            delete [] itor->second;
        }
        this->Args.clear();
    }
}