#include "core/Vec2.h"

Vec2::Vec2(float x, float y)
    : x(x)
    , y(y)
{

}

Vec2::Vec2()
    : x(0.0), y(0.0) 
{
    
}

Vec2::~Vec2() 
{

}

void Vec2::setX(float x) 
{
    this->x = x;
}

void Vec2::setY(float y) 
{
    this->y = y;
}

float Vec2::getX() const 
{
    return x;
}

float Vec2::getY() const
{
    return y;
}

float Vec2::distanceTo(const Vec2 & other)
{
    return sqrt(pow(fabs(other.x - x), 2) + pow(fabs(other.y - y), 2));
}

unique_ptr<Vec2> Vec2::subtractFrom(const Vec2 & other)
{
    return unique_ptr<Vec2>(new Vec2(other.getX()-x, other.getY()-y));
}
