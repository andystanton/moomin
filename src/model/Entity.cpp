#include "model/Entity.h"

Entity::Entity(float x, float y)
    : pos(x, y)
    , collisionType(Entity::CollisionType::circle)
    , mass(0)
{

}

Entity::~Entity() 
{

}

Vec2& Entity::getPos()
{
    return pos;
}

void Entity::setPos(Vec2 pos)
{
    this->pos = Vec2(pos);
}

Vec2& Entity::getVelocity()
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

void Entity::setCollisionType(CollisionType collisionType)
{
    this->collisionType = collisionType;
}

void Entity::setMass(float mass)
{
    this->mass = mass;
}

float Entity::getMass()
{
    return mass;
}
