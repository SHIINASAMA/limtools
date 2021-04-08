#include "file/json/JObject.hpp"
#include "io/Console.hpp"

int main()
{
    const char * content = "{\n"
                           "  \"Name\": \"Nihao\"\n"
                           "}";

    JObject* obj = new JObject();
    obj->Format(content);
    auto res = obj->Data["Name"];
    delete obj;
    return 0;
}