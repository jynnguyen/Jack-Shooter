#include "InputHandler.hpp"

void InputHandler::handleEvent(const sf::Event &event)
{
    if (const auto *key = event.getIf<sf::Event::KeyPressed>())
        keyStates[key->scancode] = true;
    else if (const auto *key = event.getIf<sf::Event::KeyReleased>())
        keyStates[key->scancode] = false;
    else if (const auto *btn = event.getIf<sf::Event::MouseButtonPressed>())
        mouseStates[btn->button] = true;
    else if (const auto *btn = event.getIf<sf::Event::MouseButtonReleased>())
        mouseStates[btn->button] = false;
}

bool InputHandler::isKeyPressed(sf::Keyboard::Scan key, float delay)
{
    if (keyStates[key])
    {
        float timePassed = keyTimers[key].getElapsedTime().asSeconds();
        if (timePassed >= delay)
        {
            keyTimers[key].restart();
            return true;
        }
    }
    return false;
}

bool InputHandler::isMouseButtonPressed(sf::Mouse::Button btn, float delay)
{
    if (mouseStates[btn])
    {
        float timePassed = mouseTimers[btn].getElapsedTime().asSeconds();
        if (timePassed >= delay)
        {
            mouseTimers[btn].restart();
            return true;
        }
    }
    return false;
}

sf::Vector2f InputHandler::getMouseCoords(const sf::RenderWindow &window) const
{
    sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return mouseCoords;
}