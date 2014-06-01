#include "drawing/GLHandler.h"

GLHandler::GLHandler(const string& title,
                     int width,
                     int height,
                     PhysicsHelper & physicsHelper)
    : title(title)
    , width(width)
    , height(height)
    , physicsHelper(physicsHelper)
    , renderers()
    , entityRenderer(nullptr)
    , freeTypeRenderer(nullptr)
    , frameCount(0)
    , lastFpsUpdate(0.f)
    , fps(0.f)
    , fpsString()
{

}

GLHandler::~GLHandler()
{

}

void GLHandler::recalculateFps()
{
    frameCount++;
    float currentTime = glfwGetTime();

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

void GLHandler::registerRenderer(Renderer * renderer)
{
    renderers.insert(renderer);
    renderer->handleResize(width, height);
}

void GLHandler::setEntityRenderer(EntityRenderer * entityRenderer)
{
    this->entityRenderer = entityRenderer;
    registerRenderer(this->entityRenderer);
}

void GLHandler::setFreeTypeRenderer(FreeTypeRenderer * freeTypeRenderer)
{
    this->freeTypeRenderer = freeTypeRenderer;
    registerRenderer(this->freeTypeRenderer);

    Text * fpsText = new Text(fpsString, width/2 - 42, height/2 - 15, FontProvider::FontFamily::VeraMono, 32, Text::Colour::WHITE);
    Text * titleText = new Text(title, 4, height/2 - 15, FontProvider::FontFamily::VeraMono, 32, Text::Colour::WHITE);

    freeTypeRenderer->addText(titleText);
    freeTypeRenderer->addText(fpsText);
}

void GLHandler::init()
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        cerr << "Error: Unable to initialise GLEW" << endl;
        exit( EXIT_FAILURE );
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.2, 0.2, 0.5, 1.0);
}

void GLHandler::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    recalculateFps();

    entityRenderer->draw();
    freeTypeRenderer->draw();
}

void GLHandler::resize()
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION );
    glLoadIdentity();

    glOrtho(0, physicsHelper.getWidth(), 0, physicsHelper.getHeight(), 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (auto renderer : renderers)
    {
        renderer->handleResize(width, height);
    }
}
