#ifndef _MOOMIN_RENDERER
#define _MOOMIN_RENDERER

class Renderer
{
public:
    virtual ~Renderer() {};
    virtual void draw() = 0;
};

#endif
