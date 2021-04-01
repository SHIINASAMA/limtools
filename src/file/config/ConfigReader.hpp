/**
 * @file ConfigReader.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief Config文件读取类声明
 * @version 0.1
 * @date 2021-04-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <map>
#include "../../io/File.hpp"
#include "ConfigProperty.hpp"

#ifndef _CONFIGREADER_HPP_
#define _CONFIGREADER_HPP_

/**
 * @brief Config文件读取类
 * 
 */
class ConfigReader
{
public:
    /**
     * @brief 从文件中读取Config
     * 
     * @param path 文件路径
     * @param propertyMap 目标Map
     * @return true 读取成功
     * @return false 读取失败
     */
    static bool Read(char *path, std::map<char *, char *, cmp> *propertyMap);

    /**
     * @brief 释放由ConfigReader::Read分配的内存
     * 
     * @param toFreeMap 目标Map
     */
    static void FreeMap(std::map<char *, char *, cmp> *toFreeMap);
};

#endif