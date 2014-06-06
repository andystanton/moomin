#include "model/Entity.hpp"

Entity::Entity(Vec2 pos, Entity::CollisionType collisionType, Mesh mesh, Vec2 velocity)
    : pos(pos)
    , nextPos(pos)
    , velocity(velocity)
    , collisionType(collisionType)
    , mesh(mesh)
{

}

Entity::~Entity()
{

}

const Mesh & Entity::getMesh() const
{
    return mesh;
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
