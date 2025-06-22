#pragma once
#include "main.hpp"
#include "AssetManager.hpp"

class Game;

class GameAssets
{
    friend class Game;
private:
    ~GameAssets();

    sf::Clock clock;
    sf::Font font;
    sf::Text *text = nullptr;
    sf::Music bgm;
    vector<sf::Sprite> sprites;
    unsigned score = 0;
    sf::RectangleShape button;

    bool createText(string fontPath, unsigned int size = 30);
    bool createBgm(string musicPath, unsigned int vol = 100);
    bool createButton(const sf::RenderWindow &window); // for testing
    bool createSprite(string texPath, sf::Vector2f pos = {0,0});
    
    void setTextString(string str);
};