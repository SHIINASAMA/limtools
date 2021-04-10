#include "file/json/JObject.hpp"
#include "io/Console.hpp"

int main()
{
    char *content = "{\n"
                    "  \"t\": true,\n"
                    "  \"f\": false,\n"
                    "  \"number\": 65535,\n"
                    "  \"me\": {\n"
                    "    \"name\": \"kaoru\",\n"
                    "    \"age\": 18\n"
                    "  },\n"
                    "  \"list\": [\n"
                    "    {\n"
                    "      \"name\": \"kaoru\",\n"
                    "      \"age\": 19\n"
                    "    },\n"
                    "    {\n"
                    "      \"name\": \"shiina\",\n"
                    "      \"age\": 20\n"
                    "    },\n"
                    "    {\n"
                    "      \"name\": \"kaori\",\n"
                    "      \"age\": 10\n"
                    "    }\n"
                    "  ],\n"
                    "  \"null\": null\n"
                    "}";

    JObject *obj = new JObject();
    obj->Format(content, strlen(content));

    int a;
    auto res = obj->GetInt("number", &a);

    delete obj;
    return 0;
}