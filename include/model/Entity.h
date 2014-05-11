#ifndef _MOOMIN_ENTITY
#define _MOOMIN_ENTITY

#include <initializer_list>

#include "drawing/Mesh.h"
#include "core/Vec2.h"

using std::initializer_list;

class Entity
{
public:
    enum class CollisionType
    {
        circle,
        aabb
    };

    Entity(float x, float y);
    ~Entity();

    virtual const Mesh & getMesh() const = 0;

    Vec2& getPos();
    Vec2& getVelocity();
    void setPos(Vec2);
    void setVelocity(Vec2);

    void setCollisionType(CollisionType);
    CollisionType getCollisionType();
private:
    Vec2 pos;
    Vec2 velocity;
    CollisionType collisionType;
};

#endif
