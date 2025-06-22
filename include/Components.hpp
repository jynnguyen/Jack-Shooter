#pragma once
#include "main.hpp"

class Movement
{
public:
    Movement(sf::Vector2f velocity = {0, 0}, float speed = 0, float rotSpeed = 0) : velocity(velocity), speed(speed), rotationSpeed(rotSpeed) {}
    sf::Vector2f velocity = {0, 0};
    float speed = 0;
    float rotationSpeed = 0;
};

class LifeSpan{
    public:
    LifeSpan(bool hasDuration = false, float duration = 1):hasDuration(hasDuration), duration(duration){}
    bool isAlive = true;
    bool hasDuration = true;
    float duration = 1;
};