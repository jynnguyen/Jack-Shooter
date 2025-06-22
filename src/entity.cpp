#include "Entity.hpp"

Entity::Entity(string t, string texPath) : type(t), texturePath(texPath)
{
}

Entity::~Entity()
{
    if (sprite)
        delete sprite;
}

sf::Sprite *Entity::getSprite() const
{
    return sprite;
}

string Entity::str() const
{
    ostringstream oss;
    oss << "Entity [type=" << type
        << ", texturePath=" << texturePath;

    if (sprite)
    {
        sf::Vector2f pos = sprite->getPosition();
        oss << ", spritePos=(" << pos.x << ", " << pos.y << ")";
    }
    else
    {
        oss << ", sprite=nullptr";
    }

    oss << ", movement.velocity=(" << movement.velocity.x << ", " << movement.velocity.y << ")";

    oss << ", lifeSpan={isAlive=" << (lifeSpan.isAlive ? "true" : "false")
        << ", hasDuration=" << (lifeSpan.hasDuration ? "true" : "false")
        << ", duration=" << lifeSpan.duration << "}";

    oss << "]";

    return oss.str();
}

void Entity::kill()
{
    lifeSpan.isAlive = false;
}

void Entity::setMove(sf::Vector2f velo, float speed)
{
    movement.velocity = velo;
    movement.speed = speed != 0 ? speed : movement.speed;
}

void Entity::setSpriteScale(sf::Vector2f scale)
{
    sprite->setScale(scale);
}

void Entity::checkOutsideWindow()
{
    float sizeX = sprite->getTexture().getSize().x * sprite->getScale().x / 2.f;
    float sizeY = sprite->getTexture().getSize().y * sprite->getScale().y / 2.f;
    sf::Vector2f pos = {gbFunc.getLimit(sprite->getPosition().x, sizeX, gbFunc.WIDTH - sizeX), gbFunc.getLimit(sprite->getPosition().y, sizeY, gbFunc.HEIGHT - sizeY)};
    sprite->setPosition(pos);
}
