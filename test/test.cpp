#include "file/json/JObject.hpp"
#include "io/Console.hpp"

int main()
{
//    char *content = "{\n"
//                    "  \"t\": true,\n"
//                    "  \"f\": false,\n"
//                    "  \"n\": null,\n"
//                    "  \"me\": [\n"
//                    "    {\n"
//                    "      \"A\": 10\n"
//                    "    }\n"
//                    "  ],\n"
//                    "  \"name\": \"kaoru\",\n"
//                    "  \"body\": {\n"
//                    "    \"age\": 10\n"
//                    "  }\n"
//                    "}";

    JObject *obj = new JObject();
    //obj->Format(content, strlen(content));

    obj->SetBool("false",false);
    obj->SetBool("true", true);
    obj->SetInt("int", 18);
    obj->SetDouble("double", 10.0);
    obj->SetNull("null");
    auto list = obj->SetList("list");

    JObject *temp;
    temp = list->SetObject();
    temp->SetString("name", "kaoru");
    temp->SetInt("age", 20);
    temp = list->SetObject();
    temp->SetString("name","kaori");
    temp->SetInt("age",19);

    int len = obj->Build(nullptr);
    char *buf = new char[len];
    obj->Build(buf);
    delete obj;
    return 0;
}