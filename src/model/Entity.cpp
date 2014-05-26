#include "model/Entity.h"

Entity::Entity(float x, float y, Entity::CollisionType collisionType)
    : pos(x, y)
    , nextPos(x, y)
    , velocity(0.f, 0.f)
    , collisionType(collisionType)
    , mass(0)
{

}

Entity::~Entity()
{

}

Vec2 & Entity::getPos()
{
    return pos;
}

void Entity::setPos(Vec2 pos)
{
    this->pos = Vec2(pos);
}

Vec2 & Entity::getNextPos()
{
    return nextPos;
}

void Entity::setNextPos(Vec2 nextPos)
{
    this->nextPos = Vec2(nextPos);
}

Vec2 & Entity::getVelocity()
{
    return velocity;
}

void Entity::setVelocity(Vec2 velocity)
{
    this->velocity = Vec2(velocity);
}

Entity::CollisionType Entity::getCollisionType()
{
    return collisionType;
}

void Entity::setMass(float mass)
{
    this->mass = mass;
}

float Entity::getMass()
{
    return mass;
}
