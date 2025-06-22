#pragma once

#include "main.hpp"

class InputHandler
{
public:
    void handleEvent(const sf::Event &event);
    bool isKeyPressed(sf::Keyboard::Scan key, float delay = 0.f);
    bool isMouseButtonPressed(sf::Mouse::Button button, float delay = 0.f);
    sf::Vector2f getMouseCoords(const sf::RenderWindow &window) const;

private:
    unordered_map<sf::Keyboard::Scan, bool> keyStates;
    unordered_map<sf::Mouse::Button, bool> mouseStates;

    unordered_map<sf::Keyboard::Scan, sf::Clock> keyTimers;
    unordered_map<sf::Mouse::Button, sf::Clock> mouseTimers;
};
