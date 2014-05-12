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

    float getMass();
    void setMass(float);

    Vec2& getPos();
    void setPos(Vec2);

    Vec2& getVelocity();
    void setVelocity(Vec2);

    CollisionType getCollisionType();
    void setCollisionType(CollisionType);

private:
    float mass;
    Vec2 pos;
    Vec2 velocity;
    CollisionType collisionType;
};

#endif
