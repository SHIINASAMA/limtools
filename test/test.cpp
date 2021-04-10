#include "file/json/JObject.hpp"
#include "io/Console.hpp"

int main()
{
    char *content = "{\n"
                    "  \"t\": true,\n"
                    "  \"f\": false,\n"
                    "  \"me\": {\n"
                    "    \"name\": \"kaoru\",\n"
                    "    \"age\": 18\n"
                    "  }\n"
                    "}";

    JObject *obj = new JObject();
    obj->Format(content, strlen(content));
    delete obj;
    return 0;
}