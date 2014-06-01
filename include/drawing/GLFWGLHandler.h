#ifndef _MOOMIN_GLFW_GL_HANDLER
#define _MOOMIN_GLFW_GL_HANDLER

#include "drawing/GLHandler.h"

class GLFWGLHandler
    : public GLHandler
{
public:
    GLFWGLHandler(const string& title, int width, int height, PhysicsHelper *);
    ~GLFWGLHandler();

    void draw();
    bool isActive();
    void quit();

    void handleKey(GLFWwindow * window, int key, int scancode, int action, int mods);
    void handleClick(GLFWwindow *, int button, int action, int mods);
    void handleResize(GLFWwindow * window, int windowWidth, int windowHeight);

    static GLFWGLHandler * instance;
    static void handleKeyWrapper(GLFWwindow * window, int key, int scancode, int action, int mods);
    static void handleClickWrapper(GLFWwindow *, int button, int action, int mods);
    static void handleResizeWrapper(GLFWwindow * window, int windowWidth, int windowHeight);

private:
    GLFWwindow * window;
    double clickStartX, clickStartY;
    double clickEndX, clickEndY;
};

#endif
