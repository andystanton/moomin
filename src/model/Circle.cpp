#include "model/Circle.hpp"

Circle::Circle(Vec2 pos, float radius, Vec2 velocity)
    : Entity(pos, Entity::CollisionType::circle, velocity)
    , radius(radius)
{

}

Circle::~Circle()
{

}

float Circle::getRadius()
{
    return radius;
}

const Mesh & Circle::getMesh() const
{
    return mesh;
}
