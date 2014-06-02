#ifndef _MOOMIN_GL_HANDLER
#define _MOOMIN_GL_HANDLER

#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "drawing/shader.h"

#include "model/PhysicsHelper.h"
#include "drawing/Renderer.h"
#include "drawing/EntityRenderer.h"

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

    virtual double getTime() = 0;
    virtual bool isActive() = 0;
    virtual void quit() = 0;
    virtual void draw();

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
};

#endif
