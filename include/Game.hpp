#pragma once
#include "main.hpp"
#include "InputHandler.hpp"
#include "GameAssets.hpp"
#include "EntityManager.hpp"
#include "GlobalFunc.hpp"
#include "SoundManager.hpp"
#include "Configuration.hpp"

class Game
{
public:
    Game(string configPath);
    ~Game();
    void run();

private:
    sf::RenderWindow window;
    InputHandler input;
    GameAssets assets;
    EntityManager entityManager;
    SoundManager soundManager;
    Configuration* config = nullptr;
    Entity* player = nullptr;
    float eventDelay = 0, buttonDelay = 9999999;

    void initWindow();
    void initUI();
    void initEntity();
    void handleEvents();
    void keyboardEvents();
    void mouseEvents();
    void playerMovement();
    void botMovement();
    void render();
    void update();
    void gameEvents();
    void shoot();
};