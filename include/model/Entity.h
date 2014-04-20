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

    const Mesh& getMesh();
    Vec2& getPos();
private:
    Vec2 pos;
    const Mesh& mesh;
};

#endif
