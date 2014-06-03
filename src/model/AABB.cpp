#include "model/AABB.hpp"

AABB::AABB(Vec2 pos, Vec2 bounding, Vec2 velocity)
    : Entity(pos, Entity::CollisionType::aabb, velocity)
    , bounding(bounding)
{
    mesh.setType(Mesh::MeshType::quads);
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
