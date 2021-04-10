#pragma once

#include <string.h>
#include <map>
#include <vector>
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

    static void pretreatment(char *buf, int *length);

    static int getFormLenght(const char *buf);

    void format(char *buf, int length);

    void formatArray(char *buf, int length);

    char *buf = nullptr;

public:
    std::map<char *, JObject *, cmp> *Data = nullptr;

    std::vector<JObject *> *List = nullptr;

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
     * @param length 缓存大小
     */
    void Format(char *buf, int length);

    /**
     * @brief 构建 Json
     * @details JObject -> Json
     * @param buf 目标缓存
     * @return 当 buf 为 nullptr 时返回 buf 所需长度
     */
    int Build(char *buf);

    JObjectType GetType();
};