#ifndef _MOOMIN_VEC2
#define _MOOMIN_VEC2

class Vec2
{
public:
    Vec2(float, float);
    Vec2();
    ~Vec2();
    
    void setX(float);
    void setY(float);
    float getX();
    float getY();
private:
    float x, y;
};

#endif
