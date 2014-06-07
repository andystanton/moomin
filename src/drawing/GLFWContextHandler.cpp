#include "drawing/GLFWContextHandler.hpp"

GLFWContextHandler * GLFWContextHandler::instance;

GLFWContextHandler::GLFWContextHandler(const string& title,
                                       int width,
                                       int height,
                                       PhysicsHelper & physicsHelper)
    : title { title }
    , width { width }
    , height { height }
    , fullscreen { false }
    , physicsHelper(physicsHelper)
{
    GLFWContextHandler::instance = this;
    if (!glfwInit()) {
        cerr << "Error: Unable to initialise GLFW" << endl;
        exit( EXIT_FAILURE );
    }
    init();
}

GLFWContextHandler::~GLFWContextHandler()
{

}

void GLFWContextHandler::init()
{
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(fullscreen ? width * 2 : width,
                              fullscreen ? height * 2 : height,
                              title.c_str(),
                              fullscreen ? glfwGetPrimaryMonitor() : NULL,
                              NULL);
    if (!window) {
        glfwTerminate();
        cerr << "Error: Unable to create GLFW Window" << endl;
        exit( EXIT_FAILURE );
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, GLFWContextHandler::handleResizeWrapper);
    glfwSetKeyCallback(window, GLFWContextHandler::handleKeyWrapper);
    glfwSetMouseButtonCallback(window, GLFWContextHandler::handleClickWrapper);
    glfwSetScrollCallback(window, GLFWContextHandler::handleScrollWrapper);
}

void GLFWContextHandler::setGLHandlerFullscreenCallback(void (*glHandlerFullscreenCallback)())
{
    this->glHandlerFullscreenCallback = glHandlerFullscreenCallback;
}

void GLFWContextHandler::setGLHandlerZoomCallback(void (*glHandlerZoomCallback)(double, double, double))
{
    this->glHandlerZoomCallback = glHandlerZoomCallback;
}
void GLFWContextHandler::postDraw()
{
    if (window != nullptr)
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

bool GLFWContextHandler::isActive()
{
    return !glfwWindowShouldClose(window);
}

void GLFWContextHandler::quit()
{
    glfwTerminate();
}

double GLFWContextHandler::getTime()
{
    return glfwGetTime();
}

void GLFWContextHandler::handleKey(int key, int action)
{
    if (action == GLFW_RELEASE)
    {
        switch (key) {
            case GLFW_KEY_F:
                toggleFullscreen();
                break;
            default:
                break;
        }
    }
    if (action == GLFW_PRESS)
    {
        switch (key) {
            case GLFW_KEY_SPACE:
                physicsHelper.togglePause();
                break;
            case GLFW_KEY_1:
                physicsHelper.addCirclesRandom();
                break;
            case GLFW_KEY_2:
                physicsHelper.addAABBsRandom();
                break;
            case GLFW_KEY_3:
                physicsHelper.addCirclesLatticeCentre();
                break;
            case GLFW_KEY_4:
                physicsHelper.addAABBsLatticeCentre();
                break;
            case GLFW_KEY_5:
                physicsHelper.addChaosLattice(false);
                break;
            case GLFW_KEY_6:
                physicsHelper.addChaosLattice(true);
                break;
            case GLFW_KEY_0:
                physicsHelper.disableAccelerationRules();
                break;
            case GLFW_KEY_LEFT_BRACKET:
                physicsHelper.enablePositionAccelerationRule(false);
                break;
            case GLFW_KEY_RIGHT_BRACKET:
                physicsHelper.enablePositionAccelerationRule(true);
                break;
            case GLFW_KEY_S:
                glHandlerZoomCallback(300, 200, 0.5);
                break;
            case GLFW_KEY_A:
                glHandlerZoomCallback(300, 200, -0.5);
                break;
            case GLFW_KEY_Q:
                physicsHelper.setSpawnModeCircle();
                break;
            case GLFW_KEY_W:
                physicsHelper.setSpawnModeAABB();
                break;
            case GLFW_KEY_O:
                physicsHelper.enableEntityAccelerationRule(false);
                break;
            case GLFW_KEY_P:
                physicsHelper.enableEntityAccelerationRule(true);
                break;
            case GLFW_KEY_UP:
                physicsHelper.enableDirectionAccelerationRule('N');
                break;
            case GLFW_KEY_DOWN:
                physicsHelper.enableDirectionAccelerationRule('S');
                break;
            case GLFW_KEY_LEFT:
                physicsHelper.enableDirectionAccelerationRule('W');
                break;
            case GLFW_KEY_RIGHT:
                physicsHelper.enableDirectionAccelerationRule('E');
                break;
        }
    }
}

GLFWwindow * GLFWContextHandler::getWindow()
{
    return window;
}

void GLFWContextHandler::handleClick(GLFWwindow * window, int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &clickStartX, &clickStartY);
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        glfwGetCursorPos(window, &clickEndX, &clickEndY);
        physicsHelper.spawnEntityOnTrajectory(Vec2(clickStartX, clickStartY), Vec2(clickEndX, clickEndY));
    }
}

void GLFWContextHandler::handleResize(GLFWwindow * window, int windowWidth, int windowHeight)
{
    //glfwGetFramebufferSize(window, &width, &height);
    //GLFWContextHandler::instance->resize();
}

void GLFWContextHandler::handleScroll(GLFWwindow * window, double xoffset, double yoffset)
{
    double cursorx, cursory;

    glfwGetCursorPos(window, &cursorx, &cursory);

    if (fabs(yoffset) > 0 && glHandlerZoomCallback != nullptr)
    {
        glHandlerZoomCallback(cursorx, cursory, yoffset);
    }
}

void GLFWContextHandler::handleKeyWrapper(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    GLFWContextHandler::instance->handleKey(key, action);
}

void GLFWContextHandler::handleClickWrapper(GLFWwindow * window, int button, int action, int mods)
{
    GLFWContextHandler::instance->handleClick(window, button, action);
}

void GLFWContextHandler::handleResizeWrapper(GLFWwindow * window, int width, int height)
{
    GLFWContextHandler::instance->handleResize(window, width, height);
}

void GLFWContextHandler::handleScrollWrapper(GLFWwindow * window, double xoffset, double yoffset)
{
    GLFWContextHandler::instance->handleScroll(window, xoffset, yoffset);
}

void GLFWContextHandler::toggleFullscreen()
{
    glfwDestroyWindow(window);
    window = nullptr;

    fullscreen = !fullscreen;
    init();
    if (glHandlerFullscreenCallback != nullptr)
    {
        glHandlerFullscreenCallback();
    }
}
