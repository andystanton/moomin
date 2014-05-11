#include "model/AABB.h"

AABB::AABB(float x, float y, float boundingX, float boundingY)
    : Entity(x, y)
    , bounding(boundingX, boundingY)
{
    mesh.setType(Mesh::MeshType::quads);
    setCollisionType(Entity::CollisionType::aabb);
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
