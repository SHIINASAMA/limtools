#include "JObject.hpp"

void JObject::removeSpace(const char *buf)
{
    int space_num = 0;
    int quotes_num = 0;
    for (int pos = 0; pos < this->length; pos++)
    {
        //双引号照搬并使 quotes_num 自增
        if (buf[pos] == '\"')
        {
            this->buf[pos - space_num] = buf[pos];
            quotes_num++;
            continue;
        }

        //直接照搬并跳过转义字符
        if (buf[pos] == '\\')
        {
            this->buf[pos - space_num] = buf[pos];
            this->buf[pos - space_num + 1] = buf[pos + 1];
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
                this->buf[pos - space_num] = buf[pos];
            }
        }
        //直接复制
        else
        {
            this->buf[pos - space_num] = buf[pos];
        }
    }

    this->buf[length - space_num] = '\0';
    this->length -= space_num + 1;
}

JObject::JObject(const char *buf)
{
    this->length = strlen(buf);
    this->buf = new char[this->length]{0};
    this->removeSpace(buf);
}

JObject::~JObject()
{
    if (this->buf != nullptr)
    {
        delete[] this->buf;
    }
}