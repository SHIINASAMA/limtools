#include "../../io/Console.hpp"

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

struct cmp
{
    bool operator()(const char *pc1, const char *pc2) const
    {
        return strcmp(pc1, pc2) < 0;
    }
};