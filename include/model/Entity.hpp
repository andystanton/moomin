#ifndef _MOOMIN_ENTITY
#define _MOOMIN_ENTITY

#include <initializer_list>

#include "drawing/Mesh.hpp"
#include "core/Vec2.hpp"

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

    Entity(Vec2 pos, CollisionType, Mesh mesh, Vec2 velocity);
    ~Entity();

    const Mesh & getMesh() const;

    float getMass();
    void setMass(float);

    Vec2 & getPos();
    void setPos(Vec2);

    Vec2 & getVelocity();
    void setVelocity(Vec2);

    Vec2 & getNextPos();
    void setNextPos(Vec2);

    virtual float * getColour() = 0;

    CollisionType getCollisionType();

private:
    Vec2 pos;
    Vec2 nextPos;
    Vec2 velocity;
    CollisionType collisionType;
    Mesh mesh;
};

#endif
