#pragma once

#include "main.hpp"
#include "AssetManager.hpp"

class SoundManager
{
public:
    ~SoundManager();
    sf::Sound *getSound(string soundType, string bufferPath);

private:
    unordered_map<string, sf::Sound *> sounds;
};