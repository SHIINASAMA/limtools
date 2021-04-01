#include "file/config/ConfigWriter.hpp"

void Make(ConfigProperty *property, char *Name, char *Value)
{
    strcpy(property->Name, Name);
    strcpy(property->Value, Value);
}

int main()
{
    ConfigProperty c1, c2, c3;
    Make(&c1, (char *)"Name", (char *)"Me");
    Make(&c2, (char *)"Port", (char *)"8022");
    Make(&c3, (char *)"IP Address", (char *)"0.0.0.0");
    std::vector<ConfigProperty> list;
    list.push_back(c1);
    list.push_back(c2);
    list.push_back(c3);

    auto res = ConfigWriter::Write((char *)"config", &list);
    if (res)
    {
        Console::Print("OK\n");
    }
    else
    {
        Console::Print("Error\n");
    }
    return 0;
}
