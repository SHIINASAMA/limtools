#include <map>
#include "../../io/File.hpp"
#include "ConfigProperty.hpp"

#ifndef _CONFIGREADER_HPP_
#define _CONFIGREADER_HPP_

class ConfigReader
{
public:
    static bool Read(char *path, std::map<char *, char *, cmp> *propertyMap);

    static void FreeMap(std::map<char *, char *, cmp> *toFreeMap);
};

#endif