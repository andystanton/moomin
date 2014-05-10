#include "model/AABB.h"

AABB::AABB(float x, float y, float boundingX, float boundingY)
    : Entity(x, y, mesh)
    , bounding(boundingX, boundingY)
{

}

AABB::~AABB()
{

}

Vec2 & AABB::getBounding()
{
    return bounding;
}
