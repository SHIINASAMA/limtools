#include "file/config/ConfigWriter.hpp"
#include "file/config/ConfigReader.hpp"

void Make(ConfigProperty *property, char *Name, char *Value)
{
    strcpy(property->Name, Name);
    strcpy(property->Value, Value);
}

int main()
{
    std::map<char *, char *, cmp> map;
    map.insert(std::pair<char *, char *>((char *)"Name", (char *)"Me"));
    map.insert(std::pair<char *, char *>((char *)"Port", (char *)"8022"));
    map.insert(std::pair<char *, char *>((char *)"IP Address", (char *)"0.0.0.0"));

    auto res = ConfigWriter::Write((char *)"config", &map);
    if (res)
    {
        Console::Print("Wrtier: OK\n");
    }
    else
    {
        Console::Print("Writer: Error\n");
    }

    char *name;
    char *port;
    char *ipaddr;
    std::map<char *, char *, cmp> map2;
    ConfigReader::Read((char *)"config", &map2);
    name = map2[(char *)"Name"];
    port = map2[(char *)"Port"];
    ipaddr = map2[(char *)"IP Address"];
    Console::Write("Name = %s\n", name);
    Console::Write("Port = %s\n", port);
    Console::Write("IP Address = %s\n", ipaddr);
    ConfigReader::FreeMap(&map2);
    return 0;
}
