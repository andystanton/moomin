#ifndef _MOOMIN_GL_HANDLER
#define _MOOMIN_GL_HANDLER

#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <freetype-gl.h>

#ifdef __APPLE__
    #include "OpenGL/gl.h"
    #include "OpenGL/glu.h"
#else
    #include "GL/gl.h"
    #include "GL/glu.h"
#endif



#include "model/PhysicsHelper.h"

#include "drawing/Renderer.h"
#include "drawing/FreeTypeRenderer.h"
#include "drawing/EntityRenderer.h"
#include "drawing/Text.h"
#include "drawing/FontProvider.h"

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
    void setFreeTypeRenderer(FreeTypeRenderer *);

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
    FreeTypeRenderer * freeTypeRenderer;

    int frameCount;
    float lastFpsUpdate;
    float fps;
    string fpsString;
};

#endif
