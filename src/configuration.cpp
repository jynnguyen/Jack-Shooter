#include "Configuration.hpp"

Configuration::Configuration(string configPath)
{
    ifstream config(configPath);
    if (config.is_open())
    {
        string line;
        while (getline(config, line))
        {
            if (line.find("//") == 0)
                continue;
            readConfig(line);
        }
    }
}

void Configuration::readConfig(const string &line)
{
    char type[64], texturePath[256];
    float speed, scale;
    sscanf(line.c_str(), "%63[^=]=%255[^,],%f,%f", type, texturePath, &speed, &scale);
    configMap[type] = EntityConfig(texturePath, speed, scale);
}

EntityConfig &Configuration::get(string type)
{
    return configMap[type];
}