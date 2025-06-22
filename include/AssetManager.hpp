#pragma once
#include "main.hpp"

class AssetManager
{
public:
    static AssetManager &getInstance();
    const sf::Texture &getTexture(const std::string &path);
    const sf::Font &getFont(const std::string &path);
    const sf::SoundBuffer &getSoundBuffer(const std::string &path);

    void clear();

private:
    AssetManager() = default;

    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
};

#define gbAsset AssetManager::getInstance()