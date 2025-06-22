#pragma once

#include "main.hpp"
#include "Entity.hpp"
#include "AssetManager.hpp"
#include "GlobalFunc.hpp"

class EntityManager
{
public:
    ~EntityManager();
    Entity *createEntity(string type, string texPath, sf::Vector2f pos, Movement move = Movement(), LifeSpan life = LifeSpan());
    void randomSpawn(string type, string texPath, int amount, float scale = 1.f);
    vector<Entity *> &getEntitiesVec(string type);
    unordered_map<string, vector<Entity *>> &getEntitiesMap();
    void update();
    unsigned int getCount(string type = "");

private:
    unsigned int entityCount = 0;
    unordered_map<string, vector<Entity *>> entitiesMap;
    void removeEntity();
    void moveEntity();
    void onDeath(Entity *e);
};