/**
 * @file ConfigProperty.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief Config属性类定义
 * @version 0.1
 * @date 2021-04-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ConfigProperty.hpp"

ConfigProperty::ConfigProperty() {}

void ConfigProperty::ToString(char *buf)
{
    Console::Format(buf, "%s=%s\n", this->Name, this->Value);
}

void ConfigProperty::Format(char *buf)
{
    int len1 = strlen(buf);
    int len2 = 0;
    char *p = buf;
    while (*p++ != '=')
    {
        len2++;
    }
    memcpy(this->Name, buf, len2);
#ifdef _WIN32
    strcpy_s(this->Value, p);
#elif __linux__
    strcpy(this->Value, p);
#endif
}
