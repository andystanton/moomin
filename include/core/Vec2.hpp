#ifndef _MOOMIN_VEC2
#define _MOOMIN_VEC2

#include <cmath>
#include <string>
#include <iostream>
#include <sstream>

#include "util/FloatingPointHelper.hpp"

using std::string;
using std::ostream;
using std::stringstream;

using namespace floatingPointHelper;

class Vec2
{
public:
    Vec2(float, float);
    Vec2(const Vec2 &);
    Vec2(Vec2 &&);
    Vec2();
    ~Vec2();

    void setFrom(const Vec2 &);
    void setX(float);
    void setY(float);
    void normalise();

    float getX() const;
    float getY() const;
    float getMagnitude() const;
    float distanceTo(const Vec2 &) const;

    Vec2 getNormalised() const;

    Vec2 operator=(const Vec2 &);
    Vec2 operator-() const;
    Vec2 operator+(const Vec2 &) const;
    Vec2 operator-(const Vec2 &) const;
    Vec2 operator*(float) const;
    Vec2 operator/(float) const;

    bool operator==(const Vec2 &) const;
    bool operator!=(const Vec2 &) const;

    void operator +=(const Vec2 &);
    void operator -=(const Vec2 &);
    void operator *=(float);
    void operator /=(float);

    friend Vec2 operator*(float, const Vec2 &);
    friend ostream & operator<<(ostream & os, const Vec2 &);

    string toString() const;
private:
    float x, y;
};

#endif
