#ifndef _MOOMIN_ENTITY_RENDERER
#define _MOOMIN_ENTITY_RENDERER

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <set>

#include "Renderer.h"
#include "model/Entity.h"
#include "model/Circle.h"

using std::unique_ptr;
using std::set;

class EntityRenderer : public Renderer
{
public:
    EntityRenderer(const set<Entity *>&);
    ~EntityRenderer();

    void handleResize(int width, int height);
    void draw();
private:
    const set<Entity *>& entities;
    void draw(Entity *);
};

#endif
