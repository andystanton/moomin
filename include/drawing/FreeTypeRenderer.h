#ifndef _MOOMIN_FREETYPE_RENDERER
#define _MOOMIN_FREETYPE_RENDERER

#include <string>
#include <map>
#include <iostream>

#include "Renderer.h"

#include <freetype-gl.h>
#include <mat4.h>
#include <shader.h>
#include <vertex-buffer.h>

using std::string;
using std::wstring;
using std::map;
using std::make_pair;

using std::cout;
using std::endl;

class FreeTypeRenderer : public Renderer
{
public:
    enum class Colour 
    {
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE
    };

    enum class Font 
    {
        ObelixPro,
        Vera,
        VeraMono,
        VeraMonoBold,
        VeraMonoItalic,
        VeraMonoBoldItalic
    };

    typedef struct 
    {
        float x, y, z;
        float u, v;
        vec4 color;
    } vertex_t;

    FreeTypeRenderer();
    ~FreeTypeRenderer();

    void drawText(const string& text,
                  float pos_x,
                  float pos_y,
                  Font font,
                  Colour colour) const;
    void draw() const;
    void handleResize(int width, int height);

private:
    texture_atlas_t * atlas;
    vertex_buffer_t * buffer;
    GLuint shader;
    mat4 model, view, projection;

    map<Colour, vec4> colours;
    map<Font, texture_font_t *> fonts;

    void initTextColours();
    void initTextFonts();
};

#endif