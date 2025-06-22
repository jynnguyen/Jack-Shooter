#pragma once
#include "main.hpp"

struct EntityConfig
{
    EntityConfig(string texPath = "", float speed = 0, float scale = 0) : TEXTUREPATH(texPath), SPEED(speed), SCALE(scale) {}
    string TEXTUREPATH;
    float SPEED, SCALE;
};

class Configuration
{
public:
    Configuration(string configPath);
    void readConfig(const string &line);
    EntityConfig &get(string type);

private:
    unordered_map<string, EntityConfig> configMap;
};