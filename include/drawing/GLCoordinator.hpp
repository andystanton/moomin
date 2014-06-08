#ifndef _MOOMIN_GL_COORDINATOR
#define _MOOMIN_GL_COORDINATOR

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

class GLCoordinator
{
public:
    GLCoordinator(const string& title, int width, int height, PhysicsHelper &);
    ~GLCoordinator();

    void draw();
    void quit();
    double getTime();
    bool isActive();

    static void handleFullscreenToggle();
    static void handleZoom(double x, double y, double amount);

    Vec2 screenToWorld(Vec2);
    Vec2 worldToScreen(Vec2);

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
    Vec2 viewLowerLeft;
    Vec2 viewUpperRight;
    Vec2 screenToWorldRatio;

    unique_ptr<GLContextHandler> glContextHandler;

    static GLCoordinator * instance;

    void recalculateFps();
    void init();
    void zoom(double x, double y, double amount);
};

#endif
