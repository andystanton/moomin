#ifndef _MOOMIN_ENTITY
#define _MOOMIN_ENTITY

#include <initializer_list>

#include "drawing/Mesh.h"

using std::initializer_list;

class Entity
{
public:
    Entity(const Mesh&);
    ~Entity();

    const Mesh& getMesh();
private:
    const Mesh& mesh;
};

#endif
