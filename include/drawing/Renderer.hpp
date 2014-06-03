#ifndef _MOOMIN_RENDERER
#define _MOOMIN_RENDERER

class Renderer
{
public:
    virtual ~Renderer() {};
    virtual void draw() = 0;
    virtual void handleResize(int width, int height) = 0;
};

#endif
