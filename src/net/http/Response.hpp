#pragma once

#include <map>
#include <stdio.h>
#include <string.h>

struct ucmp
{
    bool operator()(const char *pc1, const char *pc2) const
    {
        return _stricmp(pc1, pc2) < 0;
    }
};

class Response
{
public:
    Response();

    ~Response();

    std::map<char *, char *, ucmp> recvMap;
    unsigned short statusCode = 0;

    char *content;
    long len = 0;

    void Format(const char *buf, int len);
};