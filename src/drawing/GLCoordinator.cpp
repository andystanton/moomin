#include "drawing/GLCoordinator.hpp"

GLCoordinator::GLCoordinator(const string& title,
                     int width,
                     int height,
                     PhysicsHelper & physicsHelper)
    : title { title }
    , width { width }
    , height { height }
    , physicsHelper(physicsHelper)
    , worldRenderer(nullptr)
    , frameCount { 0 }
    , lastFpsUpdate { 0.f }
    , fps { 0.f }
    , fpsString()
    , zoomLowerLeft(0.f, 0.f)
    , zoomUpperRight(width * 10, height * 10)
{
    GLCoordinator::instance = this;
    glContextHandler = unique_ptr<GLContextHandler>(
        new GLFWContextHandler(title, width, height, physicsHelper)
    );
    glContextHandler->setGLCoordinatorFullscreenCallback(GLCoordinator::handleFullscreenToggle);
    glContextHandler->setGLCoordinatorZoomCallback(GLCoordinator::handleZoom);
    init();
}

GLCoordinator::~GLCoordinator()
{

}

GLCoordinator * GLCoordinator::instance;

void GLCoordinator::handleFullscreenToggle()
{
    GLCoordinator::instance->init();
}

void GLCoordinator::handleZoom(double x, double y, double amount)
{
    GLCoordinator::instance->zoom(x, y, amount);
}

void GLCoordinator::zoom(double x, double y, double amount)
{
    double noramlisedx = x * 10;
    double noramlisedy = height * 10 - y * 10;
    double normalisedAmount = amount * 8;

    if (normalisedAmount > 1) normalisedAmount = 0.8;
    if (normalisedAmount < -1) normalisedAmount = -0.8;

    Vec2 zoomDiff = zoomUpperRight - zoomLowerLeft;

    Vec2 newZoomDiff = zoomDiff * (normalisedAmount > 0 ? normalisedAmount : 1/normalisedAmount);
    newZoomDiff.setX(fabs(newZoomDiff.getX()));
    newZoomDiff.setY(fabs(newZoomDiff.getY()));
    Vec2 halfZoom = newZoomDiff / 2;

    if (fabs(newZoomDiff.getY()) > 100)
    {
        zoomLowerLeft = Vec2(noramlisedx, noramlisedy) - halfZoom;
        zoomUpperRight = Vec2(noramlisedx, noramlisedy) + halfZoom;

        if (zoomLowerLeft.getX() < 0) {
            float newUpperRightX = zoomUpperRight.getX() - zoomLowerLeft.getX();
            zoomUpperRight.setX(newUpperRightX > width * 10 ? width * 10 : newUpperRightX);
            zoomLowerLeft.setX(0);
        }
        if (zoomUpperRight.getX() > width * 10){
            float newLowerLeftX = zoomLowerLeft.getX() - (zoomUpperRight.getX() - width*10);
            zoomLowerLeft.setX(newLowerLeftX < 0 ? 0 : newLowerLeftX);
            zoomUpperRight.setX(width * 10);
        }
        if (zoomLowerLeft.getY() < 0){
            float newUpperRightY = zoomUpperRight.getY() - zoomLowerLeft.getY();
            zoomUpperRight.setY(newUpperRightY > height * 10 ? height * 10 : newUpperRightY);
            zoomLowerLeft.setY(0);
        }
        if (zoomUpperRight.getY() > height * 10){
            float newLowerLeftY = zoomLowerLeft.getY() - (zoomUpperRight.getY() - height*10);
            zoomLowerLeft.setY(newLowerLeftY < 0 ? 0 : newLowerLeftY);
            zoomUpperRight.setY(height * 10);
        }
    }

    worldRenderer->lookAt(zoomLowerLeft, zoomUpperRight);
}

void GLCoordinator::init()
{
    if (worldRenderer != nullptr)
    {
        delete worldRenderer;
    }

    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(-1);
    }
    glClearColor(0.2, 0.2, 0.5, 1.0);

    worldRenderer = new WorldRenderer(physicsHelper.getEntities(), width * 10, height * 10);
    worldRenderer->setZoom(&zoomLowerLeft, &zoomUpperRight);
}

void GLCoordinator::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    recalculateFps();

    worldRenderer->draw();

    glContextHandler->postDraw();
}

void GLCoordinator::recalculateFps()
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

bool GLCoordinator::isActive()
{
    return glContextHandler->isActive();
}

double GLCoordinator::getTime()
{
    return glContextHandler->getTime();
}

void GLCoordinator::quit()
{
    glContextHandler->quit();
}
