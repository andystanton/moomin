#ifndef _MOOMIN_GL_HANDLER
#define _MOOMIN_GL_HANDLER

#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "drawing/GLFWContextHandler.hpp"
#include "drawing/shader.hpp"
#include "drawing/Renderer.hpp"
#include "drawing/EntityRenderer.hpp"
#include "model/PhysicsHelper.hpp"

using std::set;
using std::stringstream;
using std::setprecision;
using std::fixed;
using std::cout;
using std::cerr;
using std::endl;

class GLHandler
{
public:
    GLHandler(const string& title, int width, int height, PhysicsHelper &);
    ~GLHandler();

    void setEntityRenderer(EntityRenderer *);

    void draw();
    void quit();
    double getTime();
    bool isActive();

protected:
    void recalculateFps();
    void registerRenderer(Renderer *);
    void resize();
    void init();

    string title;
    int width;
    int height;
    PhysicsHelper & physicsHelper;

private:
    set<Renderer *> renderers;
    EntityRenderer * entityRenderer;

    int frameCount;
    float lastFpsUpdate;
    float fps;
    string fpsString;

    unique_ptr<GLContextHandler> glContextHandler;

    GLuint MatrixID;
    GLuint MatrixID2;
    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 Model;
    glm::mat4 MVP;

    GLuint VertexArrayID;
    GLuint VertexArrayID2;
    GLuint programID;
    GLuint programID2;
    GLuint aabbVertexBuffer;
    GLuint circleVertexBuffer;
};

#endif
