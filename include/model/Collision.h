#ifndef _MOOMIN_COLLISION
#define _MOOMIN_COLLISION

#include "model/Entity.h"

class Collision
{
public:
    Collision(Entity & primary, Entity & secondary);
    ~Collision();

    Entity & getPrimary();
    Entity & getSecondary();
    float getDepth();

private:
    Entity & primary, & secondary;
    float depth;
};

#endif