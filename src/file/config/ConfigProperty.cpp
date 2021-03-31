#include "ConfigProperty.hpp"

ConfigProperty::ConfigProperty() {}

void ConfigProperty::ToString(char *buf)
{
    Console::Format(buf, "%s=%s\n", this->Name, this->Value);
}

void ConfigProperty::Format(char *buf)
{
    int len1 = strlen(buf);
    int len2 = 0;
    char *p = buf;
    while (*p++ != '=')
    {
        len2++;
    }
    memcpy(this->Name, buf, len2);
    strcpy(this->Value, p);
}