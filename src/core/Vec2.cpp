#include "core/Vec2.h"

Vec2::Vec2(const Vec2 & other)
    : x(other.x)
    , y(other.y)
{

}

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

void Vec2::setFrom(const Vec2 & other)
{
    this->x = other.x;
    this->y = other.y;
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

void Vec2::normalise()
{
    *this /= getMagnitude();
}

Vec2 Vec2::getNormalised() const
{
    Vec2 copy = Vec2(*this);
    copy.normalise();
    return copy;
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

bool operator==(const Vec2 & primary, const Vec2 & secondary)
{
    return primary.x == secondary.x && primary.y == secondary.y;
}

bool operator!=(const Vec2 & primary, const Vec2 & secondary)
{
    return primary.x != secondary.x || primary.y != secondary.y;
}


Vec2 operator+(const Vec2 & primary, const Vec2 & secondary)
{
    return Vec2(primary.x + secondary.x, primary.y + secondary.y);
}

Vec2 operator-(const Vec2 & primary, const Vec2 & secondary)
{
    return Vec2(primary.x - secondary.x, primary.y - secondary.y);
}

Vec2 operator-(const Vec2 & primary)
{
    return Vec2(-primary.x, -primary.y);
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
