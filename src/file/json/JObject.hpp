/**
 * @file JObject.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief Json 对象类声明
 * @version 0.1
 * @date 2021-04-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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

/**
 * @brief Json对象类
 * 
 */
class JObject
{
private:
    char *buf = nullptr;
    int length = 0;
    JObjectType type = JObjectType::JObject;

    static bool isSpace(char ch);

    static void pretreatment(char *buf, int *length);

    static int getFormLength(const char *buf);

    void format(char *buf, int length);

    void formatArray(char *buf, int length);

    int build(char *buf);

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

    /**
     * @brief 获取 JObject 类型
     * @return 类型
     */
    JObjectType GetType();

    /**
     * @brief 获取 Length 属性
     * @return Length
     */
    int GetLength();

    /**
     * @brief 获取键对应的值的 Bool 类型数据
     * @param key 目标键
     * @param buf 目标缓存
     * @return 是否获取成功
     */
    bool GetBool(char *key, bool *buf);

    /**
     * @brief 获取键对应的值的 Int 类型数据
     * @param key 目标键
     * @param buf 目标缓存
     * @return 是否获取成功
     */
    bool GetInt(char *key, int *buf);

    /**
     * @brief 获取键对应的值的 Double 类型数据
     * @param key 目标键
     * @param buf 目标缓存
     * @return 是否获取成功
     */
    bool GetDouble(char *key, double *buf);

    /**
     * @brief 获取键对应的值的 Char* 类型数据
     * @param key 目标键
     * @param buf 目标缓存
     * @return 是否获取成功
     */
    bool GetString(char *key, const char *buf);

    /**
     * @brief 获取键对应的 JObject 的 JObjectType
     * @param key 目标键
     * @param buf 目标缓存
     * @return 是否获取成功
     */
    bool GetType(char *key, JObjectType *buf);

    /**
     * @brief 获取键对应的 JObject 的 Length
     * @param key 目标键
     * @param buf 目标缓存
     * @return 是否获取成功
     */
    bool GetLength(char *key, int *buf);

    /**
     * @brief 获取数组中的元素
     * @param index 索引
     * @param buf 缓存
     * @return 是否获取成功
     */
    bool At(int index, const JObject **buf);
};