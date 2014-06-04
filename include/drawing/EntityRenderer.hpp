#ifndef _MOOMIN_ENTITY_RENDERER
#define _MOOMIN_ENTITY_RENDERER

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <set>

#include "Renderer.hpp"
#include "model/Entity.hpp"
#include "model/Circle.hpp"
#include "model/AABB.hpp"
#include "drawing/shader.hpp"

using std::unique_ptr;
using std::set;

class EntityRenderer : public Renderer
{
public:
    EntityRenderer(const set<Entity *>&);
    ~EntityRenderer();

    void handleResize(int width, int height);
    void draw(glm::mat4);
private:
    const set<Entity *>& entities;
    void draw(Entity *, glm::mat4);

    GLuint programIdAABB;
    GLuint programIdCircle;

    GLuint matrixIdAABB;
    GLuint matrixIdCircle;

    GLuint vertexArrayIdAABB;
    GLuint vertexArrayIdCircle;

    GLuint colourIdAABB;
    GLuint colourIdCircle;

    GLuint vertexBufferAABB;
    GLuint vertexBufferCircle;
};

#endif
