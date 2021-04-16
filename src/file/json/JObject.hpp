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
    static bool isSpace(char ch);

    static void pretreatment(char *buf, int *length);

    static int getFormLength(const char *buf);

    void format(char *buf, int length);

    void formatArray(char *buf, int length);

    int build(char *buf);

    bool set(const char *key, JObjectType type, const char *buf);

private:

    /**
     * @brief 数据缓存
     */
    char *buf = nullptr;

    /**
     * 缓存大小（包括\0）
     */
    int length = 0;

    /**
     * 数据类型
     */
    JObjectType type = JObjectType::JObject;

    /**
     * @brief JObject 存值处
     */
    std::map<char *, JObject *, cmp> *Data = nullptr;

    /**
     * @brief Array 存值处
     */
    std::vector<JObject *> *List = nullptr;
public:

    /**
     * @brief 构造函数
     *
     * @param type 数据类型，默认为 JObject
     */
    explicit JObject(JObjectType type = JObjectType::JObject);

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
    void Format(const char *buf, int length);

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

    /**
     * @brief 设置键对应的值的 bool 类型数据
     * @param key 目标键
     * @param buf 目标值
     * @return 是否设置成功
     */
    bool SetBool(const char *key, bool buf);

    /**
     * @brief 设置键对应的值的 int 类型数据
     * @param key 目标键
     * @param buf 目标值
     * @return 是否设置成功
     */
    bool SetInt(const char *key, int buf);

    /**
     * @brief 设置键对应的值的 double 类型数据
     * @param key 目标键
     * @param buf 目标值
     * @return 是否设置成功
     */
    bool SetDouble(const char *key, double buf);

    /**
     * @brief 设置键对应的值的 char* 类型数据
     * @param key 目标键
     * @param buf 目标值
     * @return 是否设置成功
     */
    bool SetString(const char *key, const char *buf);

    /**
     * @brief 设置键对应的值的为 null
     * @param key 目标键
     * @return 是否设置成功
     */
    bool SetNull(const char *key);

    /**
     * @brief 添加键为 key 的数组
     * @param key 目标键
     * @return 添加成功返回数组 JObject 对象的指针
     */
    JObject *SetList(const char *key);

    /**
     * @brief 添加键为 key 的 JObject
     * @param key 目标键
     * @return 添加成功返回 JObject 的 JObject 对象的指针
     */
    JObject *SetJObject(const char *key);

    /**
     * @brief 为数组 JObject 对象添加一个 JObject 的 JObject 对象指针
     * @return 添加成功返回 JObject 的 JObject 对象的指针
     */
    JObject *SetObject();

    /**
     * @brief 移除数组下标为 index 的元素
     * @param index 索引值
     * @return 是否删除成功
     */
    bool Remove(int index);

    /**
     * @brief 移除键为 key 的元素
     * @param key 目标键
     * @return 是否删除成功
     */
    bool Remove(const char *key);

    /**
     * @brief 获取 JObject 或者 Array 中元素的个数
     * @return 元素的个数
     */
    int GetSize();

    /**
     * @brief 查找改键是否存在
     * @param key 目标键
     * @return 查找成功返回 true，不存在或查找失败返回 false
     */
    bool Find(const char *key);
};