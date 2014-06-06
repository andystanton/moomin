#include "model/AABB.hpp"

AABB::AABB(Vec2 pos, Vec2 bounding, Vec2 velocity)
    : Entity(pos, Entity::CollisionType::aabb, velocity)
    , bounding(bounding)
    , mesh
    {
        0.f,             0.f,
        0.f,             bounding.getY(),
        bounding.getX(), bounding.getY(),
        0.f,             0.f,
        bounding.getX(), bounding.getY(),
        bounding.getX(), 0.f
    }
{
}

AABB::~AABB()
{

}

Vec2 & AABB::getBounding()
{
    return bounding;
}

const Mesh & AABB::getMesh() const
{
    return mesh;
}
