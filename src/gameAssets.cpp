#include "GameAssets.hpp"

GameAssets::~GameAssets()
{
    if (text)
        delete text;
}

bool GameAssets::createText(string fontPath, unsigned int size)
{
    try
    {
        text = new sf::Text(gbAsset.getFont(fontPath));
        text->setCharacterSize(size);
        return true;
    }
    catch (const exception &e)
    {
        cerr << "Error setting up text: " << e.what() << '\n';
        return false;
    }
}

bool GameAssets::createBgm(string musicPath, unsigned int vol)
{
    if (!bgm.openFromFile(musicPath))
        return false;
    bgm.setVolume(vol);
    bgm.setLooping(true);
    bgm.play();
    return true;
}

bool GameAssets::createButton(const sf::RenderWindow &window)
{
    sf::Vector2f windowSize = sf::Vector2f(window.getSize());
    button.setSize(windowSize / 10.f);
    button.setFillColor(sf::Color::Green);
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(5);
    sf::Vector2f pos(windowSize.x / 2.f - button.getSize().x / 2.f, windowSize.y / 1.25f - button.getSize().y / 2.f);
    button.setPosition(pos);
    return true;
}

bool GameAssets::createSprite(string texPath, sf::Vector2f pos)
{
    sf::Sprite sprite(gbAsset.getTexture(texPath));
    sprite.setPosition(pos);
    sprites.emplace_back(sprite);
    return true;
}

void GameAssets::setTextString(string str)
{
    if (text)
        text->setString(str);
}