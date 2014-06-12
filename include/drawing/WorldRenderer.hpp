#ifndef _MOOMIN_WORLD_RENDERER
#define _MOOMIN_WORLD_RENDERER

#include <OpenGLES/ES3/gl.h>

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

class WorldRenderer : public Renderer
{
public:
    WorldRenderer(const set<Entity *>&, int width, int height, int programId);
    ~WorldRenderer();

    void draw();
    void lookAt(Vec2 bottomLeft, Vec2 topRight);
    void setZoom(Vec2 * lowerLeft, Vec2 * upperRight);
private:
    const set<Entity *>& entities;
    int width, height;
    void draw(Entity *);
    void drawGrid(int spacing);
    void drawView();

    glm::mat4 Model;
    glm::mat4 View;
    glm::mat4 Projection;
    glm::mat4 MVP;

    GLuint programId;
    GLuint matrixId;
    GLuint colourId;
    GLuint offsetId;

    GLuint vertexArrayIdGrid;
    GLuint vertexArrayIdAABB;
    GLuint vertexArrayIdCircle;

    GLuint vertexBufferGrid;
    GLuint vertexBufferAABB;
    GLuint vertexBufferCircle;

    Vec2 * zoomLowerLeft;
    Vec2 * zoomUpperRight;
};

#endif
