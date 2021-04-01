/**
 * @file ConfigWriter.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief Config文件写入类声明
 * @version 0.1
 * @date 2021-04-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <map>
#include "../../io/File.hpp"
#include "ConfigProperty.hpp"

#ifndef _CONFIGWRITER_HPP_
#define _CONFIGWRITER_HPP_

/**
 * @brief Config文件写入类
 * 
 */
class ConfigWriter
{
public:
    /**
     * @brief 向文件写入Config
     * 
     * @param path 文件路径
     * @param propertyMap 目标Map
     * @return true 写入成功
     * @return false 写入失败
     */
    static bool Write(char *path, std::map<char *, char *, cmp> *propertyMap);
};

#endif