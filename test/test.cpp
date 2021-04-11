#include "file/json/JObject.hpp"
#include "io/Console.hpp"

int main()
{
    char *content = "{\n"
                    "  \"t\": true,\n"
                    "  \"f\": false,\n"
                    "  \"n\": null,\n"
                    "  \"me\": [\n"
                    "    {\n"
                    "      \"A\": 10\n"
                    "    }\n"
                    "  ],\n"
                    "  \"name\": \"kaoru\",\n"
                    "  \"body\": {\n"
                    "    \"age\": 10\n"
                    "  }\n"
                    "}";

    JObject *obj = new JObject();
    obj->Format(content, strlen(content));

    int len = obj->Build(nullptr);
    char *buf = new char[len];
    obj->Build(buf);
    delete obj;
    return 0;
}