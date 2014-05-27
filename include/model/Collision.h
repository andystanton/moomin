#ifndef _MOOMIN_COLLISION
#define _MOOMIN_COLLISION

#include "model/Entity.h"
#include "model/Circle.h"
#include "model/AABB.h"

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
    Vec2 & getEscapeTranslation();

private:
    Entity & primary, & secondary;
    float depth;
    Vec2 resultantVelocity;
    Vec2 escapeTranslation;

    void resolveCircleCircle();
    void resolveAABBAABB();
    void resolveAABBCircle();
};

#endif
