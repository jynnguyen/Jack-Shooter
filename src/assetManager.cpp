#include "AssetManager.hpp"

AssetManager &AssetManager::getInstance()
{
    static AssetManager instance;
    return instance;
}

const sf::Texture &AssetManager::getTexture(const std::string &path)
{
    auto it = textures.find(path);
    if (it == textures.end())
    {
        sf::Texture tex;
        if (!tex.loadFromFile(path))
            throw std::runtime_error("Failed to load texture: " + path);
        textures[path] = move(tex);
    }
    return textures.at(path);
}

const sf::Font &AssetManager::getFont(const std::string &path)
{
    auto it = fonts.find(path);
    if (it == fonts.end())
    {
        sf::Font font;
        if (!font.openFromFile(path))
            throw std::runtime_error("Failed to load font: " + path);
        fonts[path] = move(font);
    }
    return fonts.at(path);
}

const sf::SoundBuffer &AssetManager::getSoundBuffer(const std::string &path)
{
    auto it = sounds.find(path);
    if (it == sounds.end())
    {
        sf::SoundBuffer sound;
        if (!sound.loadFromFile(path))
            throw std::runtime_error("Failed to load font: " + path);
        sounds[path] = move(sound);
    }
    return sounds.at(path);
}

void AssetManager::clear()
{
    textures.clear();
    fonts.clear();
}