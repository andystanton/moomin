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
    virtual void setGLHandlerCallback(void (*)()) = 0;
};

#endif
