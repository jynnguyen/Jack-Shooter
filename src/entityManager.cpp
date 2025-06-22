#include "EntityManager.hpp"

EntityManager::~EntityManager()
{
    for (auto &[key, vec] : entitiesMap)
    {
        for (auto it = vec.begin(); it != vec.end();)
        {
            delete *it;
            it = vec.erase(it);
        }
    }
}

Entity *EntityManager::createEntity(string type, string texPath, sf::Vector2f pos, Movement move, LifeSpan life)
{
    try
    {
        Entity *e = new Entity(type, texPath);
        e->sprite = new sf::Sprite(gbAsset.getTexture(texPath));
        e->movement = move;
        e->lifeSpan = life;
        e->sprite->setOrigin(e->sprite->getLocalBounds().size / 2.f);
        e->sprite->setPosition(pos);
        entitiesMap[type].emplace_back(e);
        entityCount++;
        return e;
    }
    catch (const exception &e)
    {
        cerr << " Error can't create entity : " << e.what() << "\n";
        return nullptr;
    }
}

vector<Entity *> &EntityManager::getEntitiesVec(string type)
{
    return entitiesMap[type];
}

unordered_map<string, vector<Entity *>> &EntityManager::getEntitiesMap()
{
    return entitiesMap;
}

void EntityManager::moveEntity()
{
    for (auto &[key, vec] : entitiesMap)
    {
        for (Entity *e : vec)
        {
            sf::Vector2f dir = e->movement.velocity;
            if ((dir.x != 0.f || dir.y != 0.f) && e->texturePath.find("bullet") != string::npos)
            {
                float angle = std::atan2(dir.y, dir.x) * 180.f / M_PI;
                e->sprite->setRotation(sf::degrees(angle + 90.f));
            }
            sf::Vector2f nVelocity = (e->movement.velocity != sf::Vector2f(0, 0)) ? e->movement.velocity.normalized() : sf::Vector2f(0, 0);
            e->sprite->setPosition(e->sprite->getPosition() + nVelocity * e->movement.speed);
            e->sprite->rotate(sf::degrees(e->movement.rotationSpeed));
            e->checkOutsideWindow();
        }
    }
}

void EntityManager::removeEntity()
{
    std::vector<Entity *> deadEntities;

    for (auto &[key, vec] : entitiesMap)
    {
        for (auto it = vec.begin(); it != vec.end();)
        {
            Entity *e = *it;
            e->lifeSpan.duration--;

            if (!e->lifeSpan.isAlive || (e->lifeSpan.hasDuration && e->lifeSpan.duration <= 0))
            {
                deadEntities.emplace_back(e);
                it = vec.erase(it);
                entityCount--;
            }
            else
            {
                ++it;
            }
        }
    }

    for (Entity *e : deadEntities)
    {
        if (e->type == "enemy")
            onDeath(e);
        delete e;
    }

    deadEntities.clear();
}

void EntityManager::randomSpawn(string type, string texPath, int amount, float scale)
{
    for (int i = 0; i < amount; i++)
    {
        Movement mov({1, 1}, 0);
        sf::Vector2f pos;
        int side = gbFunc.rng(0, 3);
        switch (side)
        {
        case 0:
            pos = {gbFunc.rngF(-100.f, -10.f), gbFunc.rngF(0.f, gbFunc.HEIGHT)};
            break;
        case 1:
            pos = {gbFunc.rngF(gbFunc.WIDTH + 10.f, gbFunc.WIDTH +100.f), gbFunc.rngF(0.f, gbFunc.HEIGHT)};
            break;
        case 2:
            pos = {gbFunc.rngF(0.f, gbFunc.WIDTH), gbFunc.rngF(-100.f, -10.f)};
            break;
        case 3:
            pos = {gbFunc.rngF(0.f, gbFunc.WIDTH), gbFunc.rngF(gbFunc.HEIGHT + 10.f, gbFunc.HEIGHT+100.f)};
            break;
        };
        Entity *newE = createEntity(type, texPath, pos, mov, LifeSpan());
        newE->sprite->setScale({scale, scale});
    }
}

void EntityManager::update()
{
    removeEntity();
    moveEntity();
}

unsigned int EntityManager::getCount(string type)
{
    if (type.empty())
        return entityCount;
    auto it = entitiesMap.find(type);
    if (it != entitiesMap.end())
        return it->second.size();
    else
        return 0;
}

void EntityManager::onDeath(Entity *e)
{
    vector<sf::Vector2f> directions = {
        {1.f, 1.f}, {-1.f, 1.f}, {1.f, -1.f}, {-1.f, -1.f}};

    for (const auto &dir : directions)
    {
        Entity *clone = createEntity("dieEffect", e->texturePath, e->sprite->getPosition(), e->movement, LifeSpan(true, 20));
        clone->setMove(dir, 6);
        clone->setSpriteScale({0.35, 0.35});
        clone->movement.rotationSpeed = 18;
    }
}