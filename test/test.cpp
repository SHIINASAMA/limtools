#include "file/json/JObject.hpp"
#include "io/Console.hpp"

int main()
{
    JObject *obj = new JObject();
    obj->SetBool("false",false);
    obj->SetBool("true", true);
    obj->SetInt("int", 18);
    obj->SetDouble("double", 10.0);
    obj->SetNull("null");
    obj->Remove("false");
    auto list = obj->SetList("list");

    JObject *temp;
    temp = list->SetObject();
    temp->SetString("name", "kaoru");
    temp->SetInt("age", 20);
    temp = list->SetObject();
    temp->SetString("name","kaori");
    temp->SetInt("age",19);
    temp = list->SetObject();
    temp->SetString("name","shiina");
    temp->SetInt("age",18);
    list->Remove(2);

    int len = obj->Build(nullptr);
    char *buf = new char[len];
    obj->Build(buf);
    delete obj;
    return 0;
}