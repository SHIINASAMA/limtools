#include "file/json/JObject.hpp"
#include "io/Console.hpp"

int main()
{
    char content[] = "{\"me\":[{\"A\":10}]}";

    JObject *obj = new JObject();
    obj->Format(content, strlen(content));

    int len = obj->Build(nullptr);
    delete obj;
    return 0;
}