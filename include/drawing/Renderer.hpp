#ifndef _MOOMIN_RENDERER
#define _MOOMIN_RENDERER

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer
{
public:
    virtual ~Renderer() {};
    virtual void draw(glm::mat4) = 0;
    virtual void handleResize(int width, int height) = 0;
};

#endif
