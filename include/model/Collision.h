#ifndef _MOOMIN_COLLISION
#define _MOOMIN_COLLISION

#include "model/Entity.h"
#include "model/Circle.h"

#include <iostream>
using namespace std;

class Collision
{
public:
    Collision(Entity & primary, Entity & secondary);
    ~Collision();

    Entity & getPrimary();
    Entity & getSecondary();
    float getDepth();
    Vec2 & getResultantVelocity();

private:
    Entity & primary, & secondary;
    float depth;
    Vec2 resultantVelocity;
};

#endif