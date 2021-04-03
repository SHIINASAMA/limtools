/**
 * @file ConfigProperty.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief Config属性类声明
 * @version 0.1
 * @date 2021-04-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../io/Console.hpp"
#include "../FileTools.hpp"

#define NAME_LEN 32
#define VALUE_LEN 96

#pragma once

/**
 * @brief 属性类
 * 
 */
class ConfigProperty
{
public:
    char Name[NAME_LEN]{0};
    char Value[VALUE_LEN]{0};

    ConfigProperty();

    /**
     * @brief 属性转文本
     * 
     * @param buf 目标缓存
     */
    void ToString(char *buf);

    /**
     * @brief 文本转属性
     * 
     * @param buf 目标缓存
     */
    void Format(char *buf);
};