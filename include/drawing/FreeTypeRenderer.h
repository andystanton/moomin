#ifndef _MOOMIN_FREETYPE_RENDERER
#define _MOOMIN_FREETYPE_RENDERER

#include <string>
#include <map>
#include <vector>

#include "FontProvider.h"
#include "Renderer.h"
#include "Text.h"

#include <freetype-gl.h>
#include <mat4.h>
#include <shader.h>
#include <vertex-buffer.h>

using std::string;
using std::wstring;
using std::map;
using std::make_pair;
using std::vector;

class FreeTypeRenderer : public Renderer
{
public:
    typedef struct 
    {
        float x, y, z;
        float u, v;
        vec4 color;
    } vertex_t;

    FreeTypeRenderer();
    ~FreeTypeRenderer();

    void addText(Text * text);
    void draw() const;
    void handleResize(int width, int height);

private:
    vertex_buffer_t * buffer;
    GLuint shader;
    mat4 model, view, projection;

    map<Text::Colour, vec4> colours;

    vector<Text *> textEntries;

    FontProvider * fontProvider;

    void initTextColours();
    void drawText(const string& text,
                  float x,
                  float y,
                  FontProvider::FontFamily fontFamily,
                  int size,
                  Text::Colour colour) const;
};

#endif