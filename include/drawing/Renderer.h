#ifndef _MOOMIN_RENDERER
#define _MOOMIN_RENDERER

#include <string>
#include <freetype-gl.h>
#include <GLFW/glfw3.h>

#include "FreeTypeRenderer.h"
#include "model/Entity.h"

using std::unique_ptr;
using std::string;

class Renderer
{
public:
    Renderer();
    ~Renderer();
 
    void draw() const;
    void draw(const Entity&) const;
    void writeText(const string& text) const;
};

#endif
