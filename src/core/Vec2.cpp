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

float Vec2::getMagnitude() const
{
    return sqrt(x * x + y * y);
}

float Vec2::distanceTo(const Vec2 & other)
{
    return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}

string Vec2::toString()
{
    stringstream vecString;
    vecString << *this;
    return vecString.str();
}

ostream & operator<<(ostream & os, const Vec2 & vec2)
{
    os << vec2.x << ", " << vec2.y;
    return os;
}

Vec2 operator+(const Vec2 & primary, const Vec2 & secondary)
{
    return Vec2(primary.x + secondary.x, primary.y + secondary.y);
}

Vec2 operator-(const Vec2 & primary, const Vec2 & secondary)
{
    return Vec2(primary.x - secondary.x, primary.y - secondary.y);
}

Vec2 operator*(const Vec2 & primary, float scalar)
{
    return Vec2(primary.x * scalar, primary.y * scalar);
}

Vec2 operator*(float scalar, const Vec2 & primary)
{
    return primary * scalar;
}

Vec2 operator/(const Vec2 & primary, float scalar)
{
    return Vec2(primary.x / scalar, primary.y / scalar);
}

Vec2 & operator+=(Vec2 & primary, const Vec2 & secondary)
{
    primary.x += secondary.x;
    primary.y += secondary.y;
    return primary;
}

Vec2 & operator-=(Vec2 & primary, const Vec2 & secondary)
{
    primary.x -= secondary.x;
    primary.y -= secondary.y;
    return primary;
}

Vec2 & operator*=(Vec2 & primary, float scalar)
{
    primary.x *= scalar;
    primary.y *= scalar;
    return primary;
}

Vec2 & operator/=(Vec2 & primary, float scalar)
{
    primary.x /= scalar;
    primary.y /= scalar;
    return primary;
}
