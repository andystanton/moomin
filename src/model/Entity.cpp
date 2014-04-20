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

const Vec2& Entity::getPos() const {
    return pos;
}
