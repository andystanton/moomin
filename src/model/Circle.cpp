#include "model/Circle.h"

Circle::Circle(float x, float y, float radius)
    : Entity(x, y)
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
