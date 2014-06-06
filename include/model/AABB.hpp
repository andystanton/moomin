#ifndef _MOOMIN_AABB
#define _MOOMIN_AABB

#include "model/Entity.hpp"

class AABB
    : public Entity
{
public:
    AABB(Vec2 pos, Vec2 bounding, Vec2 velocity = Vec2::ORIGIN);
    ~AABB();

    Vec2 & getBounding();

private:
    static Mesh populateMesh(Vec2);

    Vec2 bounding;
};

#endif
