#include "ConfigWriter.hpp"

bool ConfigWriter::Write(char *path, std::map<char *, char *, cmp> *propertyMap)
{
    File file;
    if (!file.Open(path, AccessMode::WRITE, OpenMode::CREATE))
    {
        return false;
    }

    ConfigProperty property;
    char buf[130];
    for (auto i = propertyMap->begin(); i != propertyMap->end(); i++)
    {
        strcpy(property.Name, i->first);
        strcpy(property.Value, i->second);
        property.ToString(buf);
        file.Write(buf, strlen(buf));
    }
    file.Close();

    return true;
}