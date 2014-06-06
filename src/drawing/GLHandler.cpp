#include "drawing/GLHandler.hpp"

GLHandler::GLHandler(const string& title,
                     int width,
                     int height,
                     PhysicsHelper & physicsHelper)
    : title { title }
    , width { width }
    , height { height }
    , physicsHelper(physicsHelper)
    , entityRenderer(nullptr)
    , frameCount { 0 }
    , lastFpsUpdate { 0.f }
    , fps { 0.f }
    , fpsString()
{
    GLHandler::instance = this;
    glContextHandler = unique_ptr<GLContextHandler>(
        new GLFWContextHandler(title, width, height, physicsHelper)
    );
    glContextHandler->setGLHandlerFullscreenCallback(GLHandler::handleFullscreenToggle);
    init();
}

GLHandler::~GLHandler()
{

}

GLHandler * GLHandler::instance;

void GLHandler::handleFullscreenToggle()
{
    GLHandler::instance->init();
}

void GLHandler::init()
{
    if (entityRenderer != nullptr)
    {
        delete entityRenderer;
    }

    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(-1);
    }
    glClearColor(0.2, 0.2, 0.5, 1.0);

    entityRenderer = new EntityRenderer(physicsHelper.getEntities(), width, height);
}

void GLHandler::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    recalculateFps();

    entityRenderer->draw();

    glContextHandler->postDraw();
}

void GLHandler::recalculateFps()
{
    frameCount++;
    float currentTime = glContextHandler->getTime();

    if (currentTime - lastFpsUpdate >= 0.5)
    {
        fps = frameCount / (currentTime - lastFpsUpdate);
        lastFpsUpdate = currentTime;

        stringstream fpsStream;
        fpsStream << setprecision(1) << fixed << fps;
        fpsString = fpsStream.str();

        frameCount = 0;
    }
}

bool GLHandler::isActive()
{
    return glContextHandler->isActive();
}

double GLHandler::getTime()
{
    return glContextHandler->getTime();
}

void GLHandler::quit()
{
    glContextHandler->quit();
}

void GLHandler::resize()
{

}
