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
    , zoomLowerLeft(0.f, 0.f)
    , zoomUpperRight(width * 10, height * 10)
{
    GLHandler::instance = this;
    glContextHandler = unique_ptr<GLContextHandler>(
        new GLFWContextHandler(title, width, height, physicsHelper)
    );
    glContextHandler->setGLHandlerFullscreenCallback(GLHandler::handleFullscreenToggle);
    glContextHandler->setGLHandlerZoomCallback(GLHandler::handleZoom);
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

void GLHandler::handleZoom(double x, double y, double amount)
{
    GLHandler::instance->zoom(x, y, amount);
}

void GLHandler::zoom(double x, double y, double amount)
{
    // int scaledWidth = width * 10;
    // int scaledHeight = height * 10;
    //entityRenderer->lookAt(Vec2(scaledWidth/2-scaledWidth/4, scaledHeight/2-scaledHeight/4), Vec2(scaledWidth-scaledWidth/4, scaledHeight-scaledHeight/4));

    double noramlisedx = x * 10;
    double noramlisedy = height * 10 - y * 10;

    cout << "zooming in on " << noramlisedx << ", " << noramlisedy << " by a factor of " << amount << endl;

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

        cout << "left was " << zoomLowerLeft.getX();
        if (zoomLowerLeft.getX() < 0) {
            cout << "left was less than 0" << endl;
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

    entityRenderer->lookAt(zoomLowerLeft, zoomUpperRight);
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

    entityRenderer = new EntityRenderer(physicsHelper.getEntities(), width * 10, height * 10);
    entityRenderer->setZoom(&zoomLowerLeft, &zoomUpperRight);
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
