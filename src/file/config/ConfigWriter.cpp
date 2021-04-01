#include "ConfigWriter.hpp"

bool ConfigWriter::Write(char *path, std::vector<ConfigProperty> *propertyList)
{
    File file;
    if (!file.Open(path, AccessMode::WRITE, OpenMode::CREATE))
    {
        return false;
    }

    char buf[130];
    for (auto i = propertyList->begin(); i != propertyList->end(); i++)
    {
        i->ToString(buf);
        file.Write(buf, strlen(buf));
    }

    return true;
}