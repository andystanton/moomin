#include "core/Vec2.hpp"

Vec2::Vec2(const Vec2 & other)
    : x(other.x)
    , y(other.y)
{

}

Vec2::Vec2(Vec2 && other)
    : x(other.x)
    , y(other.y)
{
    other.x = 0.f;
    other.y = 0.f;
}

Vec2::Vec2(float x, float y)
    : x(x)
    , y(y)
{

}

Vec2::Vec2()
    : x(0.f), y(0.f)
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

float Vec2::distanceTo(const Vec2 & other) const
{
    return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}

void Vec2::normalise()
{
    *this /= getMagnitude();
}

Vec2 Vec2::getNormalised() const
{
    Vec2 copy = *this;
    copy.normalise();
    return copy;
}

 Vec2 Vec2::operator=(const Vec2 & other) {
      this->x = other.x;
      this->y = other.y;
      return *this;
  }

bool Vec2::operator==(const Vec2 & secondary) const
{
    return almostEqual(this->x, secondary.x) && almostEqual(this->y, secondary.y);
}

bool Vec2::operator!=(const Vec2 & secondary) const
{
    return !(*this == secondary);
}

Vec2 Vec2::operator+(const Vec2 & secondary) const
{
    return Vec2(this->x + secondary.x, this->y + secondary.y);
}

Vec2 Vec2::operator-(const Vec2 & secondary) const
{
    return Vec2(this->x - secondary.x, this->y - secondary.y);
}

Vec2 Vec2::operator-() const
{
    return Vec2(-this->x, -this->y);
}

Vec2 Vec2::operator*(float scalar) const
{
    return Vec2(this->x * scalar, this->y * scalar);
}

Vec2 Vec2::operator/(float scalar) const
{
    return Vec2(this->x / scalar, this->y / scalar);
}

void Vec2::operator+=(const Vec2 & secondary)
{
    this->x += secondary.x;
    this->y += secondary.y;
}

void Vec2::operator-=(const Vec2 & secondary)
{
    this->x -= secondary.x;
    this->y -= secondary.y;
}

void Vec2::operator*=(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
}

void Vec2::operator/=(float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
}

Vec2 operator*(float scalar, const Vec2 & primary)
{
    return primary * scalar;
}

ostream & operator<<(ostream & os, const Vec2 & vec2)
{
    os << vec2.x << ", " << vec2.y;
    return os;
}

string Vec2::toString() const
{
    stringstream vecString;
    vecString << *this;
    return vecString.str();
}
