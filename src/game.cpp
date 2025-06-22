#include "Game.hpp"

Game::Game(string configPath)
{
    config = new Configuration(configPath);
    float start = assets.clock.getElapsedTime().asSeconds();
    initWindow();
    initUI();
    initEntity();
    cout << " Total init time: " << assets.clock.getElapsedTime().asSeconds() - start << " seconds\n";
}

Game::~Game()
{
    if (config)
        delete config;
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}

void Game::initWindow()
{
    const sf::VideoMode MODE({gbFunc.WIDTH, gbFunc.HEIGHT});
    const string TITLE = "Jack Shooter";
    window.create(MODE, TITLE, sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
    window.setFramerateLimit(60);
}

void Game::initUI()
{
    assets.createText("assets/PersonaAura.otf", 40);
    // assets.createBgm("assets/bgm.ogg",35);
    // assets.createButton(window);
}

void Game::initEntity()
{
    sf::Vector2f pos = {640.f, 360.f};
    const string type = "player";
    player = entityManager.createEntity(type, config->get(type).TEXTUREPATH, pos);
    player->setSpriteScale({config->get(type).SCALE, config->get(type).SCALE});
    cout << "PLAYER: " << player->str() << "\n";
}

void Game::playerMovement()
{
    sf::Vector2f dir{0.f, 0.f};

    if (input.isKeyPressed(sf::Keyboard::Scan::W))
        dir.y -= 1.f;
    if (input.isKeyPressed(sf::Keyboard::Scan::S))
        dir.y += 1.f;
    if (input.isKeyPressed(sf::Keyboard::Scan::A))
        dir.x -= 1.f;
    if (input.isKeyPressed(sf::Keyboard::Scan::D))
        dir.x += 1.f;

    if (dir.x != 0.f || dir.y != 0.f)
        player->setMove(dir, 5);
    else
        player->setMove();
}

void Game::shoot()
{

    if (input.isMouseButtonPressed(sf::Mouse::Button::Left, 0.3))
    {
        const string type = "bullet";
        sf::Sound *sound = soundManager.getSound("shoot", "assets/shoot.ogg");
        sound->play();
        Movement bulletMove({input.getMouseCoords(window) - player->getSprite()->getPosition()}, config->get(type).SPEED);
        Entity *bullet = entityManager.createEntity(type, config->get(type).TEXTUREPATH, player->getSprite()->getPosition(), bulletMove, LifeSpan(true, 45));
        bullet->setSpriteScale({config->get(type).SCALE, config->get(type).SCALE});
    }
    if (input.isMouseButtonPressed(sf::Mouse::Button::Right, 5.f))
    {
        sf::Sound *sound = soundManager.getSound("shoot", "assets/shoot.ogg");
        sound->play();
        Movement bulletMove({input.getMouseCoords(window) - player->getSprite()->getPosition()}, 15);
        Entity *bullet = entityManager.createEntity("superBullet", "assets/bullet.png", player->getSprite()->getPosition(), bulletMove, LifeSpan(true, 45));
        bullet->setSpriteScale({0.2, 0.2});
    }
}

void Game::handleEvents()
{
    while (const optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        input.handleEvent(*event);
    }
    keyboardEvents();
    mouseEvents();
}

void Game::keyboardEvents()
{
    if (input.isKeyPressed(sf::Keyboard::Scan::E, 1))
    {
        cout << " Current number of Entities: " << entityManager.getCount() << "\n";
        cout << " Player's Coordinate: " << player->getSprite()->getPosition().x << ", " << player->getSprite()->getPosition().y << "\n";
    }
}

void Game::mouseEvents()
{
}

void Game::botMovement()
{
    const string type = "enemy";
    for (Entity *e : entityManager.getEntitiesVec(type))
    {
        Movement move(player->getSprite()->getPosition() - e->getSprite()->getPosition(), gbFunc.rngF(1, 3));
        e->setMove(move.velocity, config->get(type).SPEED);
    }
}

void Game::gameEvents()
{
    for (Entity *e : entityManager.getEntitiesVec("enemy"))
    {
        optional hit = e->getSprite()->getGlobalBounds().findIntersection(player->getSprite()->getGlobalBounds());
        if (hit.has_value())
        {
            if (assets.score >= 10)
                assets.score -= 10;
            e->kill();
        }
        for (Entity *b : entityManager.getEntitiesVec("bullet"))
        {
            optional value = e->getSprite()->getGlobalBounds().findIntersection(b->getSprite()->getGlobalBounds());
            if (value.has_value())
            {
                assets.score++;
                e->kill();
                b->kill();
            }
        }
        for (Entity *b : entityManager.getEntitiesVec("superBullet"))
        {
            optional value = e->getSprite()->getGlobalBounds().findIntersection(b->getSprite()->getGlobalBounds());
            if (value.has_value())
            {
                assets.score++;
                e->kill();
            }
        }
    }
    sf::Sound *sound = soundManager.getSound("spawn", "assets/spawn.ogg");
    if (assets.clock.getElapsedTime().asSeconds() > eventDelay && entityManager.getCount("enemy") < 20)
    {
        const string type = "enemy";
        eventDelay = assets.clock.getElapsedTime().asSeconds() + 2;
        entityManager.randomSpawn(type, config->get(type).TEXTUREPATH, gbFunc.getLimit(assets.score * 0.5, 1, 10), config->get(type).SCALE);
    }
    if (sound->getStatus() == sf::Sound::Status::Playing && entityManager.getCount("enemy") <= 0)
        sound->stop();
    else if (sound->getStatus() == sf::Sound::Status::Stopped)
        sound->play();
    playerMovement();
    shoot();
    botMovement();
}

void Game::render()
{
    window.clear();
    if (assets.text)
        window.draw(*assets.text);

    for (const auto [key, vec] : entityManager.getEntitiesMap())
        for (const Entity *e : vec)
            window.draw(*e->getSprite());

    window.display();
}

void Game::update()
{
    gameEvents();
    stringstream ss;
    ss << " == SCORE: " << assets.score << " == \n";
    ss << " == TIME PLAYED: " << assets.clock.getElapsedTime().asSeconds() << " seconds ==\n";
    assets.setTextString(ss.str());
    entityManager.update();
}
