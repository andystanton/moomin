#ifndef _MOOMIN_GLFW_GL_HANDLER
#define _MOOMIN_GLFW_GL_HANDLER

#include "drawing/GLHandler.h"
#include <GLFW/glfw3.h>

class GLFWGLHandler
    : public GLHandler
{
public:
    GLFWGLHandler(const string& title, int width, int height, PhysicsHelper *);
    ~GLFWGLHandler();

    void draw();
    bool isActive();
    void quit();

    void handleKey(int key, int action);
    void handleClick(int button, int action);
    void handleResize(GLFWwindow * window, int windowWidth, int windowHeight);

    static GLFWGLHandler * instance;
    static void handleKeyWrapper(GLFWwindow *, int key, int scancode, int action, int mods);
    static void handleClickWrapper(GLFWwindow *, int button, int action, int mods);
    static void handleResizeWrapper(GLFWwindow * window, int windowWidth, int windowHeight);

private:
    GLFWwindow * window;
    double clickStartX, clickStartY;
    double clickEndX, clickEndY;
};

#endif
