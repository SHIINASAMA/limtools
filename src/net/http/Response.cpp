#include "Response.hpp"

Response::Response() {}

Response::~Response()
{
    for (auto itor = this->recvMap.begin(); itor != this->recvMap.end(); itor++)
    {
        delete itor->first;
        delete itor->second;
    }

    delete this->content;
}

void Response::Format(const char *buf, int len)
{
    char statusCode[4];
    int statusLine = 0;
    for (int i = 0; i < len; i++)
    {
        if (buf[i] == '\r' && buf[i + 1] == '\n')
        {
            statusLine = i - 1;
            break;
        }
    }

    memcpy(statusCode, &buf[9], 3);
    statusCode[3] = '\0';
    this->statusCode = (statusCode[0] - 48) * 100 + (statusCode[1] - 48) * 10 + (statusCode[2] - 48);

    int pos1 = 0;
    int pos2 = statusLine + 3;
    int prepos = 0;
    for (int i = statusLine + 3; i < len - 2; i++)
    {
        if (buf[i] == ':' && buf[i + 1] == ' ')
        {
            pos1 = i - 1;
            i += 2;
            continue;
        }

        if (buf[i] == '\r' && buf[i + 1] == '\n')
        {
            prepos = pos2;
            pos2 = i + 2;
            i += 2;
            char *name = new char[pos1 - prepos + 2];
            memcpy(name, &buf[prepos], pos1 - prepos + 1);
            name[pos1 - prepos + 1] = '\0';

            char *value = new char[pos2 - pos1 - 4];
            memcpy(value, &buf[pos1 + 3], pos2 - pos1 - 5);
            value[pos2 - pos1 - 5] = '\0';
            this->recvMap.insert(std::pair<char *, char *>(name, value));
        }
    }
}