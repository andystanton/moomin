#ifndef _MOOMIN_ENTITY_RENDERER
#define _MOOMIN_ENTITY_RENDERER

#include <vector>

#include "Renderer.h"

#include <freetype-gl.h>
#include <GLFW/glfw3.h>

#include "model/Entity.h"

using std::unique_ptr;
using std::vector;

class EntityRenderer : public Renderer
{
public:
    EntityRenderer(vector<Entity *> *);
    ~EntityRenderer();
 
    void draw() const;
private:
    vector<Entity *> * entities;
    void draw(const Entity *) const;
    void handleResize(int width, int height);
};

#endif
