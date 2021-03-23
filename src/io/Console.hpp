/**
 * @file Console.hpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 控制台库声明
 * @version 0.1
 * @date 2021-03-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**
 * @brief 控制台库
 * 
 */
class Console{
private:
    static void Put(char* str);

public:
    /**
     * @brief 输出一个浮点数
     * 
     * @param d 目标浮点数
     */
    static void Put(double d);

    /**
     * @brief 输出一个整型
     * 
     * @param l 目标整型
     * @param raidx 目标进制
     */
    static void Put(long l,int raidx = 10);

    // static void Put(unsigned long l,int raidx = 10);

    /**
     * @brief 输出一个字符
     * 
     * @param ch 目标字符
     */
    static void Put(char ch);

    /**
     * @brief 格式化输出语句
     * 
     * @param str 格式语句
     * @param ... 参数
     */
    static void Write(const char* str,...);
};
