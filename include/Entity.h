#ifndef _MOOMIN_ENTITY
#define _MOOMIN_ENTITY

#include <vector>
#include "Mesh.h"

class Entity
{
public:
    Entity();
    ~Entity();
    
private:
    Mesh mesh;
};

#endif
