#include "file/config/ConfigProperty.hpp"

int main()
{
    ConfigProperty config;
    strcpy(config.Name,"Name");
    strcpy(config.Value,"Value");
    char str[128];
    config.ToString(str);
    config.Format((char*)"VALUE=NAME");
    return 0;
}
