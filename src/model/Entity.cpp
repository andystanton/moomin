#include "model/Entity.h"

Entity::Entity(float x, float y, const Mesh& mesh)
    : pos(x, y)
    , mesh(mesh)
{

}

Entity::~Entity() 
{

}

const Mesh& Entity::getMesh() const
{
    return mesh;
}

const Vec2& Entity::getPos() const 
{
    return pos;
}

void Entity::setPos(Vec2 pos)
{
    this->pos = Vec2(pos);
}

const Vec2& Entity::getVelocity() const
{
    return velocity;
}

void Entity::setVelocity(Vec2 velocity)
{
    this->velocity = Vec2(velocity);
}