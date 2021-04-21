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

Request::Request(const char *url, const char *ipaddr, unsigned short port) {
#ifdef _WIN32
    strcpy_s(this->url, url);
    strcpy_s(this->ipaddr, ipaddr);
#elif __linux__
    strcpy(this->url, url);
    strcpy(this->ipaddr, ipaddr);
#endif
    this->port = port;
}

Request::~Request() {
    if (this->response != nullptr) {
        delete this->response;
    }
}

Response *Request::Get() {
    //请求行以及参数
    char request_line[1024]{0};
    sprintf(request_line, "GET %s HTTP/1.1\r\n", this->url);
    this->Args.insert(0, request_line);
    this->Args.append("\r\n");

    //连接服务器
    auto socket = new Socket(SocketMode::Client, this->ipaddr, this->port);
    if (socket->Connect()) {
        return nullptr;
    }

    //发送请求头
    if (!socket->Write(this->Args.c_str(), this->Args.length())) {
        return nullptr;
    }

    this->response = new Response();
    char recv_buf[4096]{0};
    int recv_length = socket->Read(recv_buf, 4096);

    //报文头
    int status_line_length = 0;
    for (int i = 0; i < recv_length; i++) {
        if (recv_buf[i] == '\r' && recv_buf[i + 1] == '\n') {
            status_line_length = i + 1;
            break;
        }
    }

    //状态码
    this->response->StatusCode = (recv_buf[9] - 48) * 100 +
                                 (recv_buf[10] - 48) * 10 +
                                 (recv_buf[11] - 48);

    //报文参数
    int header_length = 0;
    int prepos = status_line_length + 1;
    int pos1 = prepos;
    int pos2 = prepos;
    for (int i = prepos; i < recv_length; i++) {
        //键值分割点
        if (recv_buf[i] == ':' && recv_buf[i + 1] == ' ') {
            pos1 = i - 1;
            i += 2;
        }
            //行末
        else if (recv_buf[i] == '\r' && recv_buf[i + 1] == '\n') {
            prepos = pos2;
            pos2 = i + 2;
            i += 2;

            int key_length = pos1 - prepos + 1;
            char *key = new char[key_length + 1];
            memcpy(key, &recv_buf[prepos], key_length);
            key[key_length] = '\0';

            int value_length = pos2 - pos1 - 5;
            char *value = new char[value_length + 1];
            memcpy(value, &recv_buf[pos1 + 3], value_length);
            value[value_length] = '\0';

            this->response->Args.insert(std::make_pair(key, value));

            if (recv_buf[i] == '\r' && recv_buf[i + 1] == '\n') {
                header_length = i + 2;
                break;
            }
        }
    }

    //读取不完整，做失败处理
    if (header_length == 0) {
        return nullptr;
    }

    if (this->response->Args.count((char *) "Content-Length") == 1) {
        this->response->ContentLength = atol(this->response->Args[(char *) "Content-Length"]);
        this->response->Content = new char[this->response->ContentLength + 1];

        //报头完整且包含正文
        if (recv_length - header_length >= 0) {
            memcpy(this->response->Content, &recv_buf[header_length], recv_length - header_length);
        }

        //循环读取避免超过最大长度
        int surplus_length = this->response->ContentLength - (recv_length - header_length);
        while (surplus_length) {
            int l = socket->Read(&this->response->Content[this->response->ContentLength - surplus_length], 4096);
            if (!l) {
                return nullptr;
            }

            surplus_length -= l;
        }
        this->response->Content[this->response->ContentLength] = '\0';
    }

    socket->Close();
    delete socket;
    return this->response;
}

Response *Request::Post(const char *content, int size) {
    //请求行以及参数
    char request_line[1024]{0};
    sprintf(request_line, "POST %s HTTP/1.1\r\n", this->url);
    this->Args.insert(0, request_line);
    this->Args.append("\r\n");

    //连接服务器
    auto socket = new Socket(SocketMode::Client, this->ipaddr, this->port);
    if (socket->Connect()) {
        return nullptr;
    }

    //发送请求头
    if (!socket->Write(this->Args.c_str(), this->Args.length())) {
        return nullptr;
    }

    //POST报文
    if (!socket->Write(content, size)) {
        return nullptr;
    }

    this->response = new Response();
    char recv_buf[4096]{0};
    int recv_length = socket->Read(recv_buf, 4096);

    //报文头
    int status_line_length = 0;
    for (int i = 0; i < recv_length; i++) {
        if (recv_buf[i] == '\r' && recv_buf[i + 1] == '\n') {
            status_line_length = i + 1;
            break;
        }
    }

    //状态码
    this->response->StatusCode = (recv_buf[9] - 48) * 100 +
                                 (recv_buf[10] - 48) * 10 +
                                 (recv_buf[11] - 48);

    //报文参数
    int header_length = 0;
    int pre_pos = status_line_length + 1;
    int pos1 = pre_pos;
    int pos2 = pre_pos;
    for (int i = pre_pos; i < recv_length; i++) {
        //键值分割点
        if (recv_buf[i] == ':' && recv_buf[i + 1] == ' ') {
            pos1 = i - 1;
            i += 2;
        }
            //行末
        else if (recv_buf[i] == '\r' && recv_buf[i + 1] == '\n') {
            pre_pos = pos2;
            pos2 = i + 2;
            i += 2;

            int key_length = pos1 - pre_pos + 1;
            char *key = new char[key_length + 1];
            memcpy(key, &recv_buf[pre_pos], key_length);
            key[key_length] = '\0';

            int value_length = pos2 - pos1 - 5;
            char *value = new char[value_length + 1];
            memcpy(value, &recv_buf[pos1 + 3], value_length);
            value[value_length] = '\0';

            this->response->Args.insert(std::make_pair(key, value));

            if (recv_buf[i] == '\r' && recv_buf[i + 1] == '\n') {
                header_length = i + 2;
                break;
            }
        }
    }

    //读取不完整，做失败处理
    if (header_length == 0) {
        return nullptr;
    }

    if (this->response->Args.count((char *) "Content-Length") == 1) {
        this->response->ContentLength = atol(this->response->Args[(char *) "Content-Length"]);
        this->response->Content = new char[this->response->ContentLength + 1];

        //报头完整且包含正文
        if (recv_length - header_length >= 0) {
            memcpy(this->response->Content, &recv_buf[header_length], recv_length - header_length);
        }

        //循环读取避免超过最大长度
        int surplus_length = this->response->ContentLength - (recv_length - header_length);
        while (surplus_length) {
            int l = socket->Read(&this->response->Content[this->response->ContentLength - surplus_length], 4096);
            if (!l) {
                return nullptr;
            }

            surplus_length -= l;
        }
        this->response->Content[this->response->ContentLength] = '\0';
    }

    socket->Close();
    delete socket;
    return this->response;
}

void Request::SetArg(const char *key, const char *value) {
    char buf[512]{0};
    sprintf(buf, "%s: %s\r\n", key, value);
    Args.append(buf);
}
