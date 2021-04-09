#include "file/json/JObject.hpp"
#include "io/Console.hpp"

int main()
{
    const char *content = "{\"Name\": \"Mike\",\"Age\": 18,\"Sex\": null,\"F\": false,\"T\": true}";

    JObject *obj = new JObject();
    obj->Format(content);
    auto res = obj->Data;
    delete obj;
    return 0;
}