#ifndef _MOOMIN_ENTITY_RENDERER
#define _MOOMIN_ENTITY_RENDERER

#include <set>

#include "Renderer.h"

#include <freetype-gl.h>
#include <GLFW/glfw3.h>

#include "model/Entity.h"

using std::unique_ptr;
using std::set;

class EntityRenderer : public Renderer
{
public:
    EntityRenderer(const set<Entity *>&);
    ~EntityRenderer();
 
    void draw() const;
private:
    const set<Entity *>& entities;
    void draw(const Entity *) const;
    void handleResize(int width, int height);
};

#endif
