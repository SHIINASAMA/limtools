/**
 * @file JObject.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief Json 对象类定义
 * @version 0.1
 * @date 2021-04-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "JObject.hpp"

JObject::JObject()
{
}

JObject::~JObject()
{
    if (this->buf != nullptr)
    {
        delete[] this->buf;
    }

    if (this->type == JObjectType::JObject)
    {
        for (auto itor = this->Data->begin(); itor != this->Data->end(); itor++)
        {
            delete[] itor->first;
            delete itor->second;
        }

        delete this->Data;
    }
    else if (this->type == JObjectType::Array)
    {
        for (auto itor = this->List->begin(); itor != this->List->end(); itor++)
        {
            delete *itor;
        }

        delete this->List;
    }
}

void JObject::format(char *buf, int length)
{
    int start_pos = -1;  //第一个双引号
    int medium_pos = -1; //第二个双引号
    int end_pos = 0;    //逗号或者反花括号
    int quotes_num = 0; //双引号的数目
    char *key = nullptr;
    for (int i = 0; i < length; i++)
    {
        //转义符号直接跳过
        if (buf[i] == '\\')
        {
            i++;
            continue;
        }

        if (buf[i] == '\"')
        {
            if (quotes_num % 2 == 0)
            {
                //第一个双引号
                if (start_pos == -1)
                {
                    start_pos = i;
                }
            }
            else
            {
                //第二个双引号
                if (medium_pos == -1)
                {
                    medium_pos = i;

                    int key_length = medium_pos - start_pos;
                    key = new char[key_length];
                    memcpy(key, &buf[start_pos + 1], key_length - 1);
                    key[key_length - 1] = '\0';
                }
            }
            quotes_num++;
            continue;
        }

        if ((buf[i] == ',' || buf[i] == '}' || buf[i] == ']') && quotes_num % 2 == 0)
        {
            end_pos = i;

            for (int j = medium_pos + 1; j < end_pos; j++)
            {
                if (buf[j] == '\"')
                {
                    for (int k = end_pos - 1; k > medium_pos; k--)
                    {
                        if (buf[k] == '\"')
                        {
                            //String
                            auto child = new JObject();
                            child->type = JObjectType::String;

                            int value_length = k - j;
                            child->buf = new char[value_length];
                            memcpy(child->buf, &buf[j + 1], value_length - 1);
                            child->buf[value_length - 1] = '\0';
                            child->length = value_length;

                            this->Data->insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                            goto end;
                        }
                        else if (!isSpace(buf[end_pos - 1]))
                        {
                            delete key;
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                            break;
                        }
                    }
                }
                else if (buf[j] == '{')
                {
                    //JObject
                    auto child = new JObject();
                    child->type = JObjectType::JObject;
                    child->Data = new std::map<char *, JObject *, cmp>();

                    int value_length = getFormLength(&buf[j]);
                    child->buf = new char[value_length + 2];
                    memcpy(child->buf, &buf[j + 1], value_length + 1);
                    child->buf[value_length + 1] = '\0';

                    child->format(child->buf, value_length + 1);

                    this->Data->insert(std::make_pair(key, child));
                    key = nullptr;
                    start_pos = -1;
                    medium_pos = -1;
                    i = j + value_length + 2;
                    goto end;
                }
                else if (buf[j] == '[')
                {
                    //Array
                    auto child = new JObject();
                    child->type = JObjectType::Array;
                    child->List = new std::vector<JObject *>();

                    int value_length = getFormLength(&buf[j]);
                    child->buf = new char[value_length + 1];
                    memcpy(child->buf, &buf[j + 1], value_length);
                    child->buf[value_length] = '\0';

                    child->formatArray(child->buf, value_length);

                    this->Data->insert(std::make_pair(key, child));

                    key = nullptr;
                    start_pos = -1;
                    medium_pos = -1;
                    i = j + value_length + 2;
                    goto end;
                }
                else if (buf[j + 0] == 'f' &&
                         buf[j + 1] == 'a' &&
                         buf[j + 2] == 'l' &&
                         buf[j + 3] == 's' &&
                         buf[j + 4] == 'e')
                {
                    for (int k = end_pos - 1; k > medium_pos; k--)
                    {
                        if (buf[k] == 'e' && &buf[k] == &buf[j + 4])
                        {
                            //BOOL:false
                            auto child = new JObject();
                            child->type = JObjectType::Bool;

                            int value_length = k - j + 2;
                            child->buf = new char[value_length];
                            memcpy(child->buf, &buf[j], value_length - 1);
                            child->buf[value_length - 1] = '\0';
                            child->length = value_length;

                            this->Data->insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                            goto end;
                        }
                        else if (!isSpace(buf[k]))
                        {
                            delete key;
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                            break;
                        }
                    }
                    delete key;
                    key = nullptr;
                    start_pos = -1;
                    medium_pos = -1;
                    break;
                }
                else if (buf[j + 0] == 't' &&
                         buf[j + 1] == 'r' &&
                         buf[j + 2] == 'u' &&
                         buf[j + 3] == 'e')
                {
                    for (int k = end_pos - 1; k > medium_pos; k--)
                    {
                        if (buf[k] == 'e' && &buf[k] == &buf[j + 3])
                        {
                            //BOOL:true
                            auto child = new JObject();
                            child->type = JObjectType::Bool;

                            int value_length = k - j + 2;
                            child->buf = new char[value_length];
                            memcpy(child->buf, &buf[j], value_length - 1);
                            child->buf[value_length - 1] = '\0';
                            child->length = value_length;

                            this->Data->insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                            goto end;
                        }
                        else if (!isSpace(buf[k]))
                        {
                            delete key;
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                            break;
                        }
                    }
                    delete key;
                    key = nullptr;
                    start_pos = -1;
                    medium_pos = -1;
                    break;
                }
                else if (buf[j + 0] == 'n' &&
                         buf[j + 1] == 'u' &&
                         buf[j + 2] == 'l' &&
                         buf[j + 3] == 'l')
                {
                    for (int k = end_pos - 1; k > medium_pos; k--)
                    {
                        if (buf[k] == 'l' && &buf[k] == &buf[j + 3])
                        {
                            //Null
                            auto child = new JObject();
                            child->type = JObjectType::Null;

                            int value_length = k - j + 2;
                            child->buf = new char[value_length];
                            memcpy(child->buf, &buf[j], value_length - 1);
                            child->buf[value_length - 1] = '\0';
                            child->length = value_length;

                            this->Data->insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                            goto end;
                        }
                        else if (!isSpace(buf[k]))
                        {
                            delete key;
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                            break;
                        }
                    }
                    delete key;
                    key = nullptr;
                    start_pos = -1;
                    medium_pos = -1;
                    break;
                }
                else if (buf[j] >= '0' && buf[j] <= '9')
                {
                    for (int k = end_pos - 1; k > medium_pos; k--)
                    {
                        if (buf[k] >= '0' && buf[k] <= '9')
                        {
                            //Number
                            auto child = new JObject();
                            child->type = JObjectType::Number;

                            int value_length = k - j + 2;
                            child->buf = new char[value_length];
                            memcpy(child->buf, &buf[j], value_length - 1);
                            child->buf[value_length - 1] = '\0';
                            child->length = value_length;

                            this->Data->insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                            goto end;
                        }
                        else if (!isSpace(buf[k]))
                        {
                            delete key;
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                            break;
                        }
                    }
                    delete key;
                    key = nullptr;
                    start_pos = -1;
                    medium_pos = -1;
                    break;
                }
                else
                {
                    if (buf[j] == ':')
                    {
                        continue;
                    }

                    if (!isSpace(buf[j]))
                    {
                        delete key;
                        key = nullptr;
                        start_pos = -1;
                        medium_pos = -1;
                        break;
                    }
                }
            }
        }
        end:
        continue;
    }

    if (this->type == JObjectType::JObject)
    {
        delete this->buf;
        this->buf = nullptr;
        this->length = 0;
    }
}

void JObject::formatArray(char *buf, int length)
{
    int brace = 0;
    int start = 0;
    int end = 0;
    for (int pos = 0; pos < length; pos++)
    {
        if (buf[pos] == '{')
        {
            brace++;
            if (brace == 1)
            {
                start = pos;
            }
        }
        else if (buf[pos] == '}')
        {
            brace--;
            if (brace == 0)
            {
                end = pos;

                int len = end - start + 1;
                auto child = new JObject();
                child->type = JObjectType::JObject;
                child->Data = new std::map<char *, JObject *, cmp>();

                child->buf = new char[len];
                memcpy(child->buf, &buf[start + 1], len);
                child->buf[len - 1] = '\0';

                child->format(&buf[start + 1], len);

                this->List->push_back(child);
            }
        }
    }
    delete this->buf;
    this->buf = nullptr;
}

bool JObject::isSpace(char ch)
{
    switch (ch)
    {
        case ' ':
        case '\r':
        case '\n':
            return true;
        default:
            return false;
    }
}

void JObject::pretreatment(char *buf, int *length)
{
    int space_num = 0;
    int quotes_num = 0;
    for (int pos = 0; pos < *length; pos++)
    {
        //双引号照搬并使 quotes_num 自增
        if (buf[pos] == '\"')
        {
            buf[pos - space_num] = buf[pos];
            quotes_num++;
            continue;
        }

        //直接照搬并跳过转义字符
        if (buf[pos] == '\\')
        {
            buf[pos - space_num] = buf[pos];
            buf[pos - space_num + 1] = buf[pos + 1];
            pos += 1;
            continue;
        }

        //使 space_num 自增并移除空白
        if (buf[pos] == '\n' ||
            buf[pos] == '\t' ||
            buf[pos] == '\r' ||
            buf[pos] == ' ')
        {
            //在双引号之外
            if (quotes_num % 2 == 0)
            {
                space_num++;
            }
                //双引号内的直接复制
            else
            {
                buf[pos - space_num] = buf[pos];
            }
        }
            //直接复制
        else
        {
            buf[pos - space_num] = buf[pos];
        }
    }

    buf[*length - space_num] = '\0';
    *length -= space_num + 1;
}

int JObject::getFormLength(const char *buf)
{
    switch (buf[0])
    {
        case '{': // JObject
        {
            // brace_start 必定是 0
            // case { brace_num + 1
            // case } brace_num - 1
            // case brace_num == 0, brace_end = pos
            int brace_num = 0;
            int brace_end = 0;
            for (int pos = 0;; pos++)
            {
                if (buf[pos] == '{')
                {
                    brace_num += 1;
                }
                else if (buf[pos] == '}')
                {
                    brace_num -= 1;

                    if (brace_num == 0)
                    {
                        brace_end = pos - 1;
                        break;
                    }
                }
            }
            return brace_end;
        }
        case '[': // Array
        {
            // brackets_start 必定是 0
            // case { _num + 1
            // case } brackets_num - 1
            // case brackets_num == 0, brackets_end = pos
            int brackets_num = 0;
            int brackets_end = 0;
            for (int pos = 0;; pos++)
            {
                if (buf[pos] == '[')
                {
                    brackets_num++;
                }
                else if (buf[pos] == ']')
                {
                    brackets_num--;
                    if (brackets_num == 0)
                    {
                        brackets_end = pos - 1;
                        break;
                    }
                }
            }
            return brackets_end;
        }
        default:
            return -1;
            break;
    }
}

int JObject::build(char *buf)
{
    if (buf == nullptr)
    {
        int length = 0;

        if (this->type == JObjectType::JObject)
        {
            // JObject
            int size = this->Data->size();
            //花括号数量
            length += 2;
            //逗号数量
            length += size - 1;
            //冒号和双引号数量
            length += size * 3;

            for (auto itor = this->Data->begin(); itor != this->Data->end(); itor++)
            {
                length += strlen(itor->first);

                if (itor->second->type == JObjectType::JObject || itor->second->type == JObjectType::Array)
                {
                    length += itor->second->build(nullptr);
                }
                else
                {
                    if (itor->second->type == JObjectType::String)
                    {
                        length += itor->second->length + 1;
                    }
                    else
                    {
                        length += itor->second->length - 1;
                    }
                }
            }
        }
        else
        {
            // Array
            int size = this->List->size();
            //中括号数量
            length += 2;
            //逗号数量
            length += size - 1;

            for (auto itor = this->List->begin(); itor != this->List->end(); itor++)
            {
                length += (*itor)->build(nullptr);
            }
        }
        return length;
    }
    else
    {
        int length = -1;

        if (this->type == JObjectType::JObject)
        {
            buf[++length] = '{';

            // size 大于零则要添加逗号
            int size = 0;
            for (auto itor = this->Data->begin(); itor != this->Data->end(); itor++)
            {
                if (size > 0)
                {
                    buf[++length] = ',';
                }

                // key
                buf[++length] = '\"';
                int key_length = strlen(itor->first);
                memcpy(&buf[++length], itor->first, key_length);
                buf[length += key_length] = '\"';
                buf[++length] = ':';

                if (itor->second->type == JObjectType::JObject || itor->second->type == JObjectType::Array)
                {
                    length += itor->second->build(&buf[++length]);
                }
                else
                {
                    if (itor->second->type == JObjectType::String)
                    {
                        buf[++length] = '\"';
                        int value_length = itor->second->length - 1;
                        memcpy(&buf[++length], itor->second->buf, value_length);
                        length += value_length - 1;
                        buf[++length] = '\"';
                    }
                    else
                    {
                        int value_length = itor->second->length - 1;
                        memcpy(&buf[++length], itor->second->buf, value_length);
                        length += value_length - 1;
                    }
                }

                size++;
            }

            buf[++length] = '}';
        }
        else
        {
            buf[++length] = '[';

            // size 大于零则要添加逗号
            int size = 0;
            for (auto itor = this->List->begin(); itor != this->List->end(); itor++)
            {
                if (size > 0)
                {
                    buf[++length] = ',';
                }

                length += (*itor)->build(&buf[++length]);

                size++;
            }

            buf[++length] = ']';
        }

        return length;
    }
}

void JObject::Format(char *buf, int length)
{
    this->buf = new char[length + 1];
    memcpy(this->buf, buf, length + 1);
    this->buf[length] = '\0';

    this->Data = new std::map<char *, JObject *, cmp>();

    pretreatment(this->buf, &length);
    this->length = length;
    this->format(&this->buf[1], length);
}

int JObject::Build(char *buf)
{
    auto len = this->build(buf) + 1;

    if (buf != nullptr)
    {
        buf[len] = '\0';
    }

    return len;
}

JObjectType JObject::GetType()
{
    return this->type;
}

int JObject::GetLength()
{
    return this->length;
}

bool JObject::GetBool(char *key, bool *buf)
{
    if (this->Data != nullptr)
    {
        auto itor = this->Data->find(key);
        if (itor != this->Data->end())
        {
            if (itor->second->type != JObjectType::Bool)
            {
                return false;
            }

            if (itor->first[0] == 't')
            {
                *buf = true;
            }
            else
            {
                *buf = false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool JObject::GetInt(char *key, int *buf)
{
    if (this->Data != nullptr)
    {
        auto itor = this->Data->find(key);
        if (itor != this->Data->end())
        {
            if (itor->second->type != JObjectType::Number)
            {
                return false;
            }


            sscanf(itor->second->buf, "%d", buf);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool JObject::GetDouble(char *key, double *buf)
{
    if (this->Data != nullptr)
    {
        auto itor = this->Data->find(key);
        if (itor != this->Data->end())
        {
            if (itor->second->type != JObjectType::Number)
            {
                return false;
            }

            sscanf(itor->second->buf, "%lf", buf);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool JObject::GetString(char *key, const char *buf)
{
    if (this->Data != nullptr)
    {
        auto itor = this->Data->find(key);
        if (itor != this->Data->end())
        {
            if (itor->second->type != JObjectType::String)
            {
                return false;
            }

            buf = itor->second->buf;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool JObject::GetType(char *key, JObjectType *buf)
{
    if (this->Data != nullptr)
    {
        auto itor = this->Data->find(key);
        if (itor != this->Data->end())
        {
            *buf = itor->second->type;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool JObject::GetLength(char *key, int *buf)
{
    if (this->Data != nullptr)
    {
        auto itor = this->Data->find(key);
        if (itor != this->Data->end())
        {
            *buf = itor->second->length;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool JObject::At(int index, const JObject **buf)
{
    if (this->List != nullptr)
    {
        if (index < 0 || index > this->List->size() - 1)
        {
            return false;
        }
        else
        {
            *buf = this->List->at(index);
            return true;
        }
    }
    else
    {
        return false;
    }
}
