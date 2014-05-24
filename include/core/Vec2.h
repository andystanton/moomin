#ifndef _MOOMIN_VEC2
#define _MOOMIN_VEC2

#include <cmath>
#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::ostream;
using std::stringstream;

class Vec2
{
public:
    Vec2(float, float);
    Vec2(const Vec2 &);
    Vec2();
    ~Vec2();

    void setX(float);
    void setY(float);
    void normalise();

    float getX() const;
    float getY() const;
    float getMagnitude() const;
    float distanceTo(const Vec2 &);

    Vec2 getNormalised() const;

    friend Vec2 operator+(const Vec2 &, const Vec2 &);
    friend Vec2 operator-(const Vec2 &, const Vec2 &);
    friend Vec2 operator-(const Vec2 &);
    friend Vec2 operator*(const Vec2 &, float);
    friend Vec2 operator/(const Vec2 &, float);
    friend Vec2 operator*(float, const Vec2 &);
    friend Vec2 & operator +=(Vec2 &, const Vec2 &);
    friend Vec2 & operator -=(Vec2 &, const Vec2 &);
    friend Vec2 & operator *=(Vec2 &, float);
    friend Vec2 & operator /=(Vec2 &, float);

    string toString();
    friend ostream & operator<<(ostream & os, const Vec2 &);
private:
    float x, y;
};

#endif
