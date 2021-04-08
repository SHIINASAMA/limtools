#pragma once

#include <string.h>

/**
 * @brief Json数据类型
 * 
 */
enum class JObjectType
{
    /**
     * @brief Json对象
     * 
     */
    JObject,
    /**
     * @brief 数组
     * 
     */
    Array,
    /**
     * @brief 字符串
     * 
     */
    String,
    /**
     * @brief 整型（数字）
     * 
     */
    Int,
    /**
     * @brief 浮点型（数字）
     * 
     */
    Float,
    /**
     * @brief 空
     * 
     */
    Null,
};

class JObject
{
private:
    char *buf = nullptr;
    int length = 0;
    JObjectType type = JObjectType::JObject;

    //除空操作
    void removeSpace(const char *buf);

public:
    JObject(const char *buf);

    ~JObject();
};