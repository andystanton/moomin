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
#include "drawing/WorldRenderer.hpp"
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

    void draw();
    void quit();
    double getTime();
    bool isActive();

    static void handleFullscreenToggle();
    static void handleZoom(double x, double y, double amount);

private:
    string title;
    int width;
    int height;
    PhysicsHelper & physicsHelper;
    WorldRenderer * worldRenderer;
    int frameCount;
    float lastFpsUpdate;
    float fps;
    string fpsString;
    Vec2 zoomLowerLeft;
    Vec2 zoomUpperRight;

    unique_ptr<GLContextHandler> glContextHandler;

    static GLHandler * instance;

    void recalculateFps();
    void init();
    void zoom(double x, double y, double amount);
};

#endif
