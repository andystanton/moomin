#ifndef _MOOMIN_RENDERER
#define _MOOMIN_RENDERER

#include <GLFW/glfw3.h>

#include "model/Entity.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();
 
    void draw(const Entity&);
};

#endif
