#include "SoundManager.hpp"

SoundManager::~SoundManager()
{
    for (auto it = sounds.begin(); it != sounds.end();)
    {
        if (it->second)
            delete it->second;
        it = sounds.erase(it);
    }
}

sf::Sound *SoundManager::getSound(string soundType, string bufferPath)
{
    auto it = sounds.find(soundType);
    if (it != sounds.end())
        return it->second;
    try
    {
        sf::Sound *newSound = new sf::Sound(gbAsset.getSoundBuffer(bufferPath));
        sounds[soundType] = newSound;
        return newSound;
    }
    catch (const exception &e)
    {
        cerr << " Can not create sound " << e.what() << "\n";
        return nullptr;
    }
}