#include "drawing/GLContextHandler.hpp"

void GLContextHandler::setGLCoordinatorFullscreenCallback(void (*glCoordinatorFullscreenCallback)())
{
    this->glCoordinatorFullscreenCallback = glCoordinatorFullscreenCallback;
}

void GLContextHandler::setGLCoordinatorZoomCallback(void (*glCoordinatorZoomCallback)(double, double, double))
{
    this->glCoordinatorZoomCallback = glCoordinatorZoomCallback;
}

void GLContextHandler::setGLCoordinatorDragClickCallback(void (*glCoordinatorDragClickCallback)(double, double, double, double))
{
    this->glCoordinatorDragClickCallback = glCoordinatorDragClickCallback;
}
