#ifndef _MOOMIN_VEC2
#define _MOOMIN_VEC2

#include <cmath>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>

using std::unique_ptr;
using std::string;
using std::ostream;
using std::stringstream;

class Vec2
{
public:
    Vec2(float, float);
    Vec2();
    ~Vec2();

    void setX(float);
    void setY(float);

    float getX() const;
    float getY() const;

    float getMagnitude() const;

    float distanceTo(const Vec2 &);

    friend unique_ptr<Vec2> operator+(const Vec2 &, const Vec2 &);
    friend unique_ptr<Vec2> operator-(const Vec2 &, const Vec2 &);
    friend unique_ptr<Vec2> operator*(const Vec2 &, float);
    friend unique_ptr<Vec2> operator/(const Vec2 &, float);
    friend unique_ptr<Vec2> operator*(float, const Vec2 &);
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
