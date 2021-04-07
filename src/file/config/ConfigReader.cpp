/**
 * @file ConfigReader.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief Config文件读取类定义
 * @version 0.1
 * @date 2021-04-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ConfigReader.hpp"

bool ConfigReader::Read(char *path, std::map<char *, char *, cmp> *propertyMap)
{
    File file;
    if (!file.Open(path, AccessMode::READ, OpenMode::OPEN))
    {
        return false;
    }

    char buf[130];
    int equalPos = 0;
    int enterPos = 0;
    int len = 0;

    while (1)
    {
        len = file.Read(buf, 130);
        if (!len)
        {
            break;
        }
        for (int pos = 0; pos < len; pos++)
        {
            if (buf[pos] == '=')
            {
                equalPos = pos;
                continue;
            }

            if (buf[pos] == '\n')
            {
                enterPos = pos;
                break;
            }
        }

        char *name = new char[NAME_LEN];
        char *value = new char[VALUE_LEN];
        memcpy(name, buf, equalPos);
        name[equalPos] = '\0';
        memcpy(value, &buf[equalPos + 1], enterPos - equalPos);
        value[enterPos - equalPos - 1] = '\0';

        propertyMap->insert(std::make_pair(name, value));
        file.MoveOffset(enterPos - len + 1);
    }

    return true;
}

void ConfigReader::FreeMap(std::map<char *, char *, cmp> *toFreeMap)
{
    for (auto i = toFreeMap->begin(); i != toFreeMap->end(); i++)
    {
        delete [] i->first;
        delete [] i->second;
    }
    toFreeMap->clear();
}