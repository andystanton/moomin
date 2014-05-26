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
        mock,
        circle,
        aabb
    };

    Entity(float x, float y, CollisionType);
    ~Entity();

    virtual const Mesh & getMesh() const = 0;

    float getMass();
    void setMass(float);

    Vec2 & getPos();
    void setPos(Vec2);

    Vec2 & getVelocity();
    void setVelocity(Vec2);

    Vec2 & getNextPos();
    void setNextPos(Vec2);

    CollisionType getCollisionType();

private:
    Vec2 nextPos;
    Vec2 pos;
    Vec2 velocity;
    CollisionType collisionType;
    float mass;
};

#endif
