#pragma once

#include "Response.hpp"
#include "../Socket.hpp"
#include <cstdio>
#include <string>

class Request
{
private:
    std::string send_args;
    Response *response = nullptr;
    char url[1024]{0};
    char ipaddr[16]{0};
    int port = 80;

public:
    Request(const char *url, const char *ipaddr, unsigned short port);

    ~Request();

    Response *Get();

    void SetArg(const char *key, const char *value);
};