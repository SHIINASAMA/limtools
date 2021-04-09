#pragma once

#include <string.h>
#include <map>
#include "../config/ConfigProperty.hpp"

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
     * @brief 数字
     * 
     */
    Number,
    /**
     * @brief 空
     * 
     */
    Null,
    /**
     * @brief 布尔值
     */
    Bool,
};

class JObject
{
private:
    int length = 0;
    JObjectType type = JObjectType::JObject;
    static bool isSpace(char ch);

public:

    char *buf = nullptr;
    std::map<char *, JObject *, cmp> Data;

    /**
     * @brief 构造函数
     */
    JObject();

    /**
     * @brief 销毁资源
     */
    ~JObject();

    /**
     * @brief 格式化 JObject
     * @details Json -> JObject
     * @param buf 目标缓存
     */
    void Format(const char *buf);


    /**
     * @brief 构建 Json
     * @details JObject -> Json
     * @param buf 目标缓存
     * @return 当 buf 为 nullptr 时返回 buf 所需长度
     */
    int Build(char *buf);

    JObjectType GetType();
};