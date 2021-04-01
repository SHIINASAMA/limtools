#include <vector>
#include "../../io/File.hpp"
#include "ConfigProperty.hpp"

#ifndef _CONFIGWRITER_HPP_
#define _CONFIGWRITER_HPP_

class ConfigWriter
{
public:
    static bool Write(char *path, std::vector<ConfigProperty> *propertyList);
};

#endif