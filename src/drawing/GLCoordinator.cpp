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
    , viewLowerLeft()
    , viewUpperRight(physicsHelper.getWorldWidth(), physicsHelper.getWorldHeight())
    , screenToWorldRatio(physicsHelper.getWorldWidth() / width, physicsHelper.getWorldHeight() / height)
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
    float scaleFactor = (viewUpperRight - viewLowerLeft).getX() / (width * 10) ;
    cout << "scale factor is : " << scaleFactor << endl;

    Vec2 worldCoords = screenToWorld(Vec2(x, y));

    cout << "currently looking at: " << viewLowerLeft << " to " << viewUpperRight << endl;
    cout << "cursor is at        : " << x << ", " << y << endl;
    cout << "making it           : " << (viewLowerLeft + worldCoords) << " in screen coordinates" << endl;

    double normalisedAmount = amount * 8;
    if (normalisedAmount > 1) normalisedAmount = 0.8;
    if (normalisedAmount < -1) normalisedAmount = -0.8;
    normalisedAmount = normalisedAmount >= 0 ? normalisedAmount : -1 / normalisedAmount;

    Vec2 viewDiff = (viewUpperRight - viewLowerLeft) * normalisedAmount;

    // we have the new dimensions. now just need to work out the focal point.

    if (viewDiff.getY() > 100)
    {
        Vec2 halfZoom = viewDiff / 2;
        viewLowerLeft = viewLowerLeft + worldCoords - halfZoom;
        viewUpperRight = viewLowerLeft + viewDiff;

        if (viewLowerLeft.getX() < 0) {
            float newUpperRightX = viewUpperRight.getX() - viewLowerLeft.getX();
            viewUpperRight.setX(newUpperRightX > width * 10 ? width * 10 : newUpperRightX);
            viewLowerLeft.setX(0);
        }
        if (viewUpperRight.getX() > width * 10){
            float newLowerLeftX = viewLowerLeft.getX() - (viewUpperRight.getX() - width*10);
            viewLowerLeft.setX(newLowerLeftX < 0 ? 0 : newLowerLeftX);
            viewUpperRight.setX(width * 10);
        }
        if (viewLowerLeft.getY() < 0){
            float newUpperRightY = viewUpperRight.getY() - viewLowerLeft.getY();
            viewUpperRight.setY(newUpperRightY > height * 10 ? height * 10 : newUpperRightY);
            viewLowerLeft.setY(0);
        }
        if (viewUpperRight.getY() > height * 10){
            float newLowerLeftY = viewLowerLeft.getY() - (viewUpperRight.getY() - height*10);
            viewLowerLeft.setY(newLowerLeftY < 0 ? 0 : newLowerLeftY);
            viewUpperRight.setY(height * 10);
        }
    }

    worldRenderer->lookAt(viewLowerLeft, viewUpperRight);
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
    worldRenderer->setZoom(&viewLowerLeft, &viewUpperRight);
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

Vec2 GLCoordinator::screenToWorld(Vec2 screenCoordinates)
{
    Vec2 worldCoordinates(screenCoordinates);
    worldCoordinates.setX(worldCoordinates.getX() * screenToWorldRatio.getX());
    worldCoordinates.setY(worldCoordinates.getY() * screenToWorldRatio.getY());
    return worldCoordinates;
}

Vec2 GLCoordinator::worldToScreen(Vec2 worldCoordinates)
{
    Vec2 screenCoordinates(worldCoordinates);
    worldCoordinates.setX(worldCoordinates.getX() / screenToWorldRatio.getX());
    worldCoordinates.setY(worldCoordinates.getY() / screenToWorldRatio.getY());
    return screenCoordinates;
}
