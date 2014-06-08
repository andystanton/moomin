#ifndef _MOOMIN_GL_CONTEXT_HANDLER
#define _MOOMIN_GL_CONTEXT_HANDLER

class GLContextHandler
{
public:
    virtual ~GLContextHandler() {};
    virtual void postDraw() = 0;
    virtual double getTime() = 0;
    virtual bool isActive() = 0;
    virtual void quit() = 0;

    void setGLCoordinatorFullscreenCallback(void (*)());
    void setGLCoordinatorZoomCallback(void (*)(double, double, double));
    void setGLCoordinatorDragClickCallback(void (*)(double, double, double, double));

protected:
    void (*glCoordinatorFullscreenCallback)() = nullptr;
    void (*glCoordinatorZoomCallback)(double, double, double) = nullptr;
    void (*glCoordinatorDragClickCallback)(double, double, double, double) = nullptr;
};

#endif
