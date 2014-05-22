#include "model/AABB.h"

AABB::AABB(float x, float y, float boundingX, float boundingY)
    : Entity(x, y, Entity::CollisionType::aabb)
    , bounding(boundingX, boundingY)
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
