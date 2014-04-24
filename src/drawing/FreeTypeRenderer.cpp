#include "drawing/FreeTypeRenderer.h"

void FreeTypeRenderer::initTextColours() 
{
    colours = map<Colour, vec4>();

    vec4 whiteV = {{1.0, 1.0, 1.0, 1.0}};
    vec4 blackV = {{0.0, 0.0, 0.0, 1.0}};
    vec4 redV   = {{1.0, 0.0, 0.0, 1.0}};
    vec4 greenV = {{0.0, 1.0, 0.0, 1.0}};
    vec4 blueV  = {{0.0, 0.0, 1.0, 1.0}};

    colours.insert(make_pair(Colour::WHITE, whiteV));
    colours.insert(make_pair(Colour::BLACK, blackV));
    colours.insert(make_pair(Colour::RED,   redV));
    colours.insert(make_pair(Colour::GREEN, greenV));
    colours.insert(make_pair(Colour::BLUE,  blueV));
}

void FreeTypeRenderer::initTextFonts() 
{
    fonts = map<Font, texture_font_t *>();

    texture_font_t * obelixPro = texture_font_new_from_file( atlas, 128, "lib/freetype-gl/fonts/ObelixPro.ttf" );
    texture_font_t * vera = texture_font_new_from_file( atlas, 128, "lib/freetype-gl/fonts/Vera.ttf" );
    texture_font_t * veraMono = texture_font_new_from_file( atlas, 128, "lib/freetype-gl/fonts/VeraMono.ttf" );
    texture_font_t * veraMonoBold = texture_font_new_from_file( atlas, 128, "lib/freetype-gl/fonts/VeraMoBd.ttf" );
    texture_font_t * veraMonoItalic = texture_font_new_from_file( atlas, 128, "lib/freetype-gl/fonts/VeraMoIt.ttf" );
    texture_font_t * veraMonoBoldItalic = texture_font_new_from_file( atlas, 128, "lib/freetype-gl/fonts/VeraMoBI.ttf" );

    fonts.insert(make_pair(Font::ObelixPro, obelixPro));
    fonts.insert(make_pair(Font::Vera, vera));
    fonts.insert(make_pair(Font::VeraMono, veraMono));
    fonts.insert(make_pair(Font::VeraMonoBold, veraMonoBold));
    fonts.insert(make_pair(Font::VeraMonoItalic, veraMonoItalic));
    fonts.insert(make_pair(Font::VeraMonoBoldItalic, veraMonoBoldItalic));
}

void FreeTypeRenderer::draw() const 
{
    glUseProgram(shader);
    {
        glUniform1i(glGetUniformLocation(shader, "texture"), 0);
        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, 0, model.data);
        glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, 0, view.data);
        glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, 0, projection.data);
        vertex_buffer_render(buffer, GL_TRIANGLES);
    }
    glUseProgram(0);
    vertex_buffer_clear(buffer);
}

FreeTypeRenderer::FreeTypeRenderer() 
{
    atlas = texture_atlas_new(1024, 1024, 1);
    buffer = vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f");

    shader = shader_load("lib/freetype-gl/shaders/v3f-t2f-c4f.vert",
                         "lib/freetype-gl/shaders/v3f-t2f-c4f.frag");

    mat4_set_identity(&projection);
    mat4_set_identity(&model);
    mat4_set_identity(&view);

    initTextFonts();
    initTextColours();
}

FreeTypeRenderer::~FreeTypeRenderer() 
{

}

void FreeTypeRenderer::drawText(const string& text,
                                float pos_x,
                                float pos_y,
                                Font font,
                                Colour colour) const
{
    vec2 position = {{pos_x, pos_y}};
    vec4 fg_color = colours.at(colour);
    texture_font_t * texture_font = fonts.at(font);
    wstring wstringText = wstring(text.begin(), text.end());
    const wchar_t * wcharText = wstringText.c_str();

    size_t i;
    for( i=0; i<wcslen(wcharText); ++i )
    {
        texture_glyph_t *glyph = texture_font_get_glyph( texture_font, wcharText[i] );
        float kerning = 0;
        if( i > 0)
        {
            kerning = texture_glyph_get_kerning( glyph, wcharText[i-1] );
        }
        position.x += kerning;

        /* Actual glyph */
        float x0 = (position.x + glyph->offset_x);
        float y0 = static_cast<float>(position.y + glyph->offset_y);
        float x1 = (x0 + glyph->width);
        float y1 = static_cast<float>(y0 - glyph->height);
        float s0 = glyph->s0;
        float t0 = glyph->t0;
        float s1 = glyph->s1;
        float t1 = glyph->t1;
        GLuint index = buffer->vertices->size;
        
        GLuint indices[] = 
        {
            index, index+1, index+2,
            index, index+2, index+3
        };

        vertex_t vertices[] = 
        {
            { static_cast<float>(x0),y0,0,  s0,t0,  fg_color },
            { static_cast<float>(x0),y1,0,  s0,t1,  fg_color },
            { static_cast<float>(x1),y1,0,  s1,t1,  fg_color },
            { static_cast<float>(x1),y0,0,  s1,t0,  fg_color } 
        };
        vertex_buffer_push_back_indices( buffer, indices, 6 );
        vertex_buffer_push_back_vertices( buffer, vertices, 4 );
        position.x += glyph->advance_x;
    }
}

void FreeTypeRenderer::handleResize(int width, int height)
{
    mat4_set_orthographic(&projection, 0, width, 0, height, -1, 1);
}
