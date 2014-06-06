#ifndef _MOOMIN_AABB
#define _MOOMIN_AABB

#include "model/Entity.hpp"

class AABB
    : public Entity
{
public:
    AABB(Vec2 pos, Vec2 bounding, Vec2 velocity = Vec2(0.f, 0.f));
    ~AABB();

    Vec2 & getBounding();

    const Mesh & getMesh() const;

private:
    Vec2 bounding;
    Mesh mesh;
};

#endif
