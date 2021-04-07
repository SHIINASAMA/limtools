/**
 * @file Request.cpp
 * @author kaoru (shiina_kaoru@outlook.com)
 * @brief 请求类定义
 * @version 0.1
 * @date 2021-04-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Request.hpp"

Request::Request(const char *url, const char *ipaddr, unsigned short port)
{
#ifdef _WIN32
    strcpy_s(this->url, url);
    strcpy_s(this->ipaddr, ipaddr);
#elif __linux__
    strcpy(this->url, url);
    strcpy(this->ipaddr, ipaddr);
#endif

    this->port = port;
}

Request::~Request()
{
    delete this->response;
}

Response *Request::Get()
{
    char request_line[1024]{0};
    sprintf(request_line, "GET %s HTTP/1.1\r\n", this->url);
    this->send_args.insert(0, request_line);
    this->send_args.append("\r\n");

    Socket *socket = new Socket(SocketMode::Client, this->ipaddr, this->port);
    socket->Connect();
    socket->Write(this->send_args.c_str(), this->send_args.length());

    char buf[4096]{0};
    int len = socket->Read(buf, 4096);

    this->response = new Response();
    int recved = this->response->Format(buf, len);
    if (recved != len)
    {
        if (this->response->recvMap.count((char *)"Content-Length") != 0)
        {
            long contentLen = atol(this->response->recvMap[(char *)"Content-Length"]) + 1;

            this->response->content = new char[contentLen];
            memcpy(this->response->content, &buf[recved], recved);
            socket->Read(&this->response->content[recved + 1], contentLen - recved - 2);
            this->response->content[contentLen] = '\0';
        }
    }

    socket->Close();
    delete socket;
    return this->response;
}

Response *Request::Post(const char *content, int size)
{
    char request_line[1024]{0};
    sprintf(request_line, "POST %s HTTP/1.1\r\n", this->url);
    this->send_args.insert(0, request_line);
    this->send_args.append("\r\n");

    Socket *socket = new Socket(SocketMode::Client, this->ipaddr, this->port);
    socket->Connect();
    socket->Write(this->send_args.c_str(), this->send_args.length());

    socket->Write(content, size);

    char buf[4096]{0};
    int len = socket->Read(buf, 4096);

    this->response = new Response();
    long recved = this->response->Format(buf, len);
    if (recved != len)
    {
        if (this->response->recvMap.count((char *)"Content-Length") != 0)
        {
            long contentLen = atol(this->response->recvMap[(char *)"Content-Length"]) + 1;

            this->response->content = new char[contentLen];
            memcpy(this->response->content, &buf[recved], recved);
            socket->Read(&this->response->content[recved + 1], contentLen - recved - 1);
            this->response->content[contentLen] = '\0';
        }
    }

    auto res = socket->Close();
    // delete socket;
    return this->response;
}

void Request::SetArg(const char *key, const char *value)
{
    char buf[512]{0};
    sprintf(buf, "%s: %s\r\n", key, value);
    send_args.append(buf);
}
