#pragma once

#include "main.hpp"
#include "GameAssets.hpp"
#include "Components.hpp"
#include "GlobalFunc.hpp"

class EntityManager;
class Entity
{
    friend class EntityManager;

public:
    Entity(string t, string texPath);
    ~Entity();
    sf::Sprite *getSprite() const;
    void kill();
    void checkOutsideWindow();
    void setMove(sf::Vector2f velo = {0,0}, float speed = 0);
    void setSpriteScale(sf::Vector2f scale = {1,1});
    string str() const;

private:
    string type, texturePath;
    sf::Sprite *sprite = nullptr;
    LifeSpan lifeSpan;
    Movement movement;
};