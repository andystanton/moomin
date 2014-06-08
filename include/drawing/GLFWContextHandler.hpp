#ifndef _MOOMIN_GLFW_CONTEXT_HANDLER
#define _MOOMIN_GLFW_CONTEXT_HANDLER

#include <string>
#include <GLFW/glfw3.h>
#include "model/PhysicsHelper.hpp"
#include "drawing/GLContextHandler.hpp"

using std::string;

class GLFWContextHandler
    : public GLContextHandler
{
public:
    GLFWContextHandler(const string& title, int width, int height, PhysicsHelper &);
    ~GLFWContextHandler();

    void postDraw();
    bool isActive();
    void quit();
    double getTime();
    GLFWwindow * getWindow();

private:
    GLFWwindow * window;
    const string title;
    int width, height;
    bool fullscreen;
    PhysicsHelper & physicsHelper;

    double clickStartX, clickStartY;
    double clickEndX, clickEndY;

    void init();
    void toggleFullscreen();

    void handleKey(int key, int action);
    void handleClick(GLFWwindow *, int button, int action);
    void handleScroll(GLFWwindow *, double xoffset, double yoffset);

    static GLFWContextHandler * instance;
    static void handleKeyWrapper(GLFWwindow *, int key, int scancode, int action, int mods);
    static void handleClickWrapper(GLFWwindow *, int button, int action, int mods);
    static void handleScrollWrapper(GLFWwindow *, double xoffset, double yoffset);
};

#endif
