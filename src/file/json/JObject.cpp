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

    for (auto itor = this->Data.begin(); itor != this->Data.end(); itor++)
    {
        delete[] itor->first;
        delete itor->second;
    }
}

JObjectType JObject::GetType()
{
    return this->type;
}

void JObject::Format(const char *buf)
{
    int len = strlen(buf);

    //首先确定类型
    switch (buf[0])
    {
        case '{':
            this->type = JObjectType::JObject;
            break;
        case '[':
            this->type = JObjectType::Array;
            break;
    }

    int start_pos = -1;  //第一个双引号
    int medium_pos = -1; //第二个双引号
    int end_pos = 0;    //逗号或者反花括号
    int quotes_num = 0; //双引号的数目
    char *key = nullptr;
    for (int i = 0; i < len; i++)
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

        if ((buf[i] == ',' || buf[i] == '}') && quotes_num % 2 == 0)
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

                            this->Data.insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
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
                else if (buf[j] == '{')
                {
                    for (int k = end_pos - 1; k > medium_pos; k--)
                    {
                        if (buf[k] == '}')
                        {
                            //JObject
                            auto child = new JObject();
                            child->type = JObjectType::JObject;

                            int value_length = k - j;
                            child->buf = new char[value_length];
                            memcpy(child->buf, &buf[j + 1], value_length - 1);
                            child->buf[value_length - 1] = '\0';

                            child->Format(child->buf);

                            this->Data.insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                        }
                    }
                    delete key;
                    key = nullptr;
                    start_pos = -1;
                    medium_pos = -1;
                    break;
                }
                else if (buf[j] == '[')
                {
                    for (int k = end_pos - 1; k > medium_pos; k--)
                    {
                        if (buf[k] == ']')
                        {
                            //Array
                            auto child = new JObject();
                            child->type = JObjectType::Array;

                            int value_length = k - j;
                            child->buf = new char[value_length];
                            memcpy(child->buf, &buf[j + 1], value_length - 1);
                            child->buf[value_length - 1] = '\0';

                            child->Format(child->buf);

                            this->Data.insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
                        }
                    }
                    delete key;
                    key = nullptr;
                    start_pos = -1;
                    medium_pos = -1;
                    break;
                }
                else if (buf[j + 0] == 'f' &&
                         buf[j + 1] == 'a' &&
                         buf[j + 2] == 'l' &&
                         buf[j + 3] == 's' &&
                         buf[j + 4] == 'e')
                {
                    for (int k = end_pos; k > medium_pos; k--)
                    {
                        if (buf[k] == 'e' && &buf[k] == &buf[j + 4])
                        {
                            //BOOL:false
                            auto child = new JObject();
                            child->type = JObjectType::Bool;

                            int value_length = k - j;
                            child->buf = new char[value_length];
                            memcpy(child->buf, &buf[j + 1], value_length - 1);
                            child->buf[value_length - 1] = '\0';
                            child->length = value_length;

                            this->Data.insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
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
                    for (int k = end_pos; k > medium_pos; k--)
                    {
                        if (buf[k] == 'e' && &buf[k] == &buf[j + 3])
                        {
                            //BOOL:true
                            auto child = new JObject();
                            child->type = JObjectType::Bool;

                            int value_length = k - j;
                            child->buf = new char[value_length];
                            memcpy(child->buf, &buf[j + 1], value_length - 1);
                            child->buf[value_length - 1] = '\0';
                            child->length = value_length;

                            this->Data.insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
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
                    for (int k = end_pos; k > medium_pos; k--)
                    {
                        if (buf[k] == 'l' && &buf[k] == &buf[j + 3])
                        {
                            //Null
                            auto child = new JObject();
                            child->type = JObjectType::Null;

                            int value_length = k - j;
                            child->buf = new char[value_length];
                            memcpy(child->buf, &buf[j + 1], value_length - 1);
                            child->buf[value_length - 1] = '\0';
                            child->length = value_length;

                            this->Data.insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
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
                    for (int k = end_pos; k > medium_pos; k--)
                    {
                        if (buf[k] >= '0' && buf[k] <= '9')
                        {
                            //Number
                            auto child = new JObject();
                            child->type = JObjectType::Number;

                            int value_length = k - j;
                            child->buf = new char[value_length];
                            memcpy(child->buf, &buf[j + 1], value_length - 1);
                            child->buf[value_length - 1] = '\0';
                            child->length = value_length;

                            this->Data.insert(std::make_pair(key, child));
                            key = nullptr;
                            start_pos = -1;
                            medium_pos = -1;
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
    }
}

int JObject::Build(char *buf)
{
    return 0;
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
