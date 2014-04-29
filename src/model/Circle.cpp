#include "model/Circle.h"

Circle::Circle(float x, float y, float radius)
    : Entity(x, y, mesh)
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