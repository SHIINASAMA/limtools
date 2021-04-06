/**
 * @file ConfigWriter.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief Config文件写入类定义
 * @version 0.1
 * @date 2021-04-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ConfigWriter.hpp"

bool ConfigWriter::Write(char *path, std::map<char *, char *, cmp> *propertyMap)
{
    File file;
    if (!file.Open(path, AccessMode::WRITE, OpenMode::CREATE))
    {
        return false;
    }

    ConfigProperty property;
    char buf[130];
    for (auto i = propertyMap->begin(); i != propertyMap->end(); i++)
    {
        strcpy_s(property.Name, i->first);
        strcpy_s(property.Value, i->second);
        property.ToString(buf);
        file.Write(buf, strlen(buf));
    }
    file.Close();

    return true;
}