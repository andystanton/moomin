#include "model/Entity.hpp"

Entity::Entity(Vec2 pos, Entity::CollisionType collisionType, Vec2 velocity)
    : pos(pos)
    , nextPos(pos)
    , velocity(velocity)
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
    this->pos = pos;
}

Vec2 & Entity::getNextPos()
{
    return nextPos;
}

void Entity::setNextPos(Vec2 nextPos)
{
    this->nextPos = nextPos;
}

Vec2 & Entity::getVelocity()
{
    return velocity;
}

void Entity::setVelocity(Vec2 velocity)
{
    this->velocity = velocity;
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
