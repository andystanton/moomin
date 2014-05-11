#ifndef _MOOMIN_AABB
#define _MOOMIN_AABB

#include "model/Entity.h"

class AABB
    : public Entity
{
public:
    AABB(float x, float y, float boundingX, float boundingY);
    ~AABB();

    Vec2 & getBounding();

    const Mesh & getMesh() const;

private:
    Vec2 bounding;
    Mesh mesh
    {
        0.f, 0.f, 
        0.f, bounding.getY(), 
        bounding.getX(), bounding.getY(), 
        bounding.getX(), 0.f
    };
};

#endif