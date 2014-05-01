#ifndef _MOOMIN_ENTITY
#define _MOOMIN_ENTITY

#include <initializer_list>

#include "drawing/Mesh.h"
#include "core/Vec2.h"

using std::initializer_list;

class Entity
{
public:
    Entity(float x, float y, const Mesh&);
    ~Entity();

    const Mesh& getMesh() const;

    const Vec2& getPos() const;
    const Vec2& getVelocity() const;
    void setPos(Vec2);
    void setVelocity(Vec2);
private:
    Vec2 pos;
    Vec2 velocity;
    const Mesh& mesh;
};

#endif
