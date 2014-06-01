#include "drawing/GLFWGLHandler.h"

GLFWGLHandler::GLFWGLHandler(const string& title,
                             int width,
                             int height,
                             PhysicsHelper * physicsHelper)
    : GLHandler(title, width, height, physicsHelper)
{
    if (!glfwInit()) {
        cerr << "Error: Unable to initialise GLFW" << endl;
        exit( EXIT_FAILURE );
    }
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        cerr << "Error: Unable to create GLFW Window" << endl;
        exit( EXIT_FAILURE );
    }

    GLFWGLHandler::instance = this;

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, GLFWGLHandler::handleResizeWrapper);
    glfwSetKeyCallback(window, GLFWGLHandler::handleKeyWrapper);
    glfwSetMouseButtonCallback(window, GLFWGLHandler::handleClickWrapper);
    handleResize(window, width, height);

    GLHandler::init();
}

GLFWGLHandler::~GLFWGLHandler()
{

}

GLFWGLHandler * GLFWGLHandler::instance;

void GLFWGLHandler::draw()
{
    GLHandler::draw(); // do regular draw bit first

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool GLFWGLHandler::isActive()
{
    return !glfwWindowShouldClose(window);
}

void GLFWGLHandler::quit()
{
    glfwTerminate();
}

void GLFWGLHandler::handleKey(int key, int action)
{
    if (action == GLFW_PRESS)
    {
        switch (key) {
            case GLFW_KEY_SPACE:
                physicsHelper->togglePause();
                break;
            case GLFW_KEY_1:
                physicsHelper->addCirclesRandom();
                break;
            case GLFW_KEY_2:
                physicsHelper->addAABBsRandom();
                break;
            case GLFW_KEY_3:
                physicsHelper->addCirclesLatticeCentre();
                break;
            case GLFW_KEY_4:
                physicsHelper->addAABBsLatticeCentre();
                break;
            case GLFW_KEY_5:
                physicsHelper->addChaosLattice(false);
                break;
            case GLFW_KEY_6:
                physicsHelper->addChaosLattice(true);
                break;
            case GLFW_KEY_0:
                physicsHelper->disableAccelerationRules();
                break;
            case GLFW_KEY_LEFT_BRACKET:
                physicsHelper->enablePositionAccelerationRule(false);
                break;
            case GLFW_KEY_RIGHT_BRACKET:
                physicsHelper->enablePositionAccelerationRule(true);
                break;
            case GLFW_KEY_O:
                physicsHelper->enableEntityAccelerationRule(false);
                break;
            case GLFW_KEY_P:
                physicsHelper->enableEntityAccelerationRule(true);
                break;
            case GLFW_KEY_UP:
                physicsHelper->enableDirectionAccelerationRule('N');
                break;
            case GLFW_KEY_DOWN:
                physicsHelper->enableDirectionAccelerationRule('S');
                break;
            case GLFW_KEY_LEFT:
                physicsHelper->enableDirectionAccelerationRule('W');
                break;
            case GLFW_KEY_RIGHT:
                physicsHelper->enableDirectionAccelerationRule('E');
                break;
        }
    }
}

void GLFWGLHandler::handleClick(int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &clickStartX, &clickStartY);
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        glfwGetCursorPos(window, &clickEndX, &clickEndY);

        Vec2 pos(clickStartX * 10, physicsHelper->getHeight() - (clickStartY * 10));
        Vec2 bounding(Vec2((rand() % 20) + 50, (rand() % 20) + 50));
        Vec2 velocity(clickEndX - clickStartX, -(clickEndY - clickStartY));

        physicsHelper->addAABB(pos, bounding, velocity);

        // Vec2 pos(clickStartX * 10, physicsHelper->getHeight() - (clickStartY * 10));
        // float radius = (rand() % 20) + 20;
        // Vec2 velocity(clickEndX - clickStartX, -(clickEndY - clickStartY));
        //
        // physicsHelper->addCircle(pos, radius, velocity);
    }
}

void GLFWGLHandler::handleResize(GLFWwindow * window, int windowWidth, int windowHeight)
{
    glfwGetFramebufferSize(window, &width, &height);
    GLFWGLHandler::instance->resize();
}

void GLFWGLHandler::handleKeyWrapper(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    GLFWGLHandler::instance->handleKey(key, action);
}

void GLFWGLHandler::handleClickWrapper(GLFWwindow * window, int button, int action, int mods)
{
    GLFWGLHandler::instance->handleClick(button, action);
}

void GLFWGLHandler::handleResizeWrapper(GLFWwindow * window, int windowWidth, int windowHeight)
{
    GLFWGLHandler::instance->handleResize(window, windowWidth, windowHeight);
}
