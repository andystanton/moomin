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