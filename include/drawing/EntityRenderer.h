#ifndef _MOOMIN_ENTITY_RENDERER
#define _MOOMIN_ENTITY_RENDERER

#include <freetype-gl.h>
#include <GLFW/glfw3.h>

#include "model/Entity.h"

using std::unique_ptr;
using std::string;

class EntityRenderer
{
public:
    EntityRenderer();
    ~EntityRenderer();
 
    void draw() const;
    void draw(const Entity&) const;
};

#endif
