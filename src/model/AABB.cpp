#include "model/AABB.hpp"

AABB::AABB(Vec2 pos, Vec2 bounding, Vec2 velocity)
    : Entity(pos, Entity::CollisionType::aabb, populateMesh(bounding), velocity)
    , bounding(bounding)
{
}

AABB::~AABB()
{

}

Vec2 & AABB::getBounding()
{
    return bounding;
}

float * AABB::getColour()
{
    return new float[4]{ 0.8f, 0.7f, 0.3f, 0.f };
}

Mesh AABB::populateMesh(Vec2 bounding)
{
    const int componentCount = 12;

    float meshComponents[componentCount] = {
        0.f,             0.f,
        0.f,             bounding.getY(),
        bounding.getX(), bounding.getY(),
        0.f,             0.f,
        bounding.getX(), bounding.getY(),
        bounding.getX(), 0.f
    };

    return Mesh(Mesh::MeshType::triangles, meshComponents, componentCount);
}
