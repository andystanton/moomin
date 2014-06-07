#ifndef _MOOMIN_ENTITY_RENDERER
#define _MOOMIN_ENTITY_RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    EntityRenderer(const set<Entity *>&, int width, int height);
    ~EntityRenderer();

    void draw();
    void lookAt(Vec2 bottomLeft, Vec2 topRight);
    void setZoom(Vec2 * lowerLeft, Vec2 * upperRight);
private:
    const set<Entity *>& entities;
    void draw(Entity *);

    glm::mat4 Model;
    glm::mat4 View;
    glm::mat4 Projection;
    glm::mat4 MVP;

    GLuint programId;
    GLuint matrixId;
    GLuint colourId;
    GLuint offsetId;

    GLuint vertexArrayIdAABB;
    GLuint vertexArrayIdCircle;

    GLuint vertexBufferAABB;
    GLuint vertexBufferCircle;

    Vec2 * zoomLowerLeft;
    Vec2 * zoomUpperRight;
};

#endif
