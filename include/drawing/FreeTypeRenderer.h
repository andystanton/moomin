#ifndef _MOOMIN_FREETYPE_RENDERER
#define _MOOMIN_FREETYPE_RENDERER

#include <string>
#include <map>
#include <vector>

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
    void drawText(const string& text,
                  float pos_x,
                  float pos_y,
                  Text::Font font,
                  Text::Colour colour) const;
    void draw() const;
    void handleResize(int width, int height);

private:
    texture_atlas_t * atlas;
    vertex_buffer_t * buffer;
    GLuint shader;
    mat4 model, view, projection;

    map<Text::Colour, vec4> colours;
    map<Text::Font, texture_font_t *> fonts;

    vector<Text *> textEntries;

    void initTextColours();
    void initTextFonts();
};

#endif