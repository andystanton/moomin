#include "drawing/Renderer.h"

#include <stdio.h>
#include <wchar.h>

#include <cmath>

#include <freetype-gl.h>
#include <mat4.h>
#include <shader.h>
#include <vertex-buffer.h>

#include <GLFW/glfw3.h>


typedef struct {
    float x, y, z;
    float u, v;
    vec4 color;
} vertex_t;

texture_atlas_t * atlas;
vertex_buffer_t * buffer;
GLuint shader;
mat4   model, view, projection;

void reshape(GLFWwindow* window, int width, int height ) {
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION );
    glLoadIdentity();
    glScalef(1.0, -1.0, 1.0);
    glOrtho(0, width, height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW );
    mat4_set_orthographic( &projection, 0, w, 0, h, -1, 1);
    glLoadIdentity();
    
}


void drawText(){
    glUseProgram( shader );
    {
        glUniform1i( glGetUniformLocation( shader, "texture" ), 0 );
        glUniformMatrix4fv( glGetUniformLocation( shader, "model" ), 1, 0, model.data);
        glUniformMatrix4fv( glGetUniformLocation( shader, "view" ), 1, 0, view.data);
        glUniformMatrix4fv( glGetUniformLocation( shader, "projection" ), 1, 0, projection.data);
        vertex_buffer_render( buffer, GL_TRIANGLES );
    }

}

void add_text( vertex_buffer_t * buffer, texture_font_t * font,
               wchar_t *text, vec2 pen, vec4 fg_color_1, vec4 fg_color_2 )
{
    size_t i;
    for( i=0; i<wcslen(text); ++i )
    {
        texture_glyph_t *glyph = texture_font_get_glyph( font, text[i] );
        float kerning = 0;
        if( i > 0)
        {
            kerning = texture_glyph_get_kerning( glyph, text[i-1] );
        }
        pen.x += kerning;

        /* Actual glyph */
        float x0  = ( pen.x + glyph->offset_x );
        float y0  = static_cast<float>( pen.y + glyph->offset_y );
        float x1  = ( x0 + glyph->width );
        float y1  = static_cast<float>( y0 - glyph->height );
        float s0 = glyph->s0;
        float t0 = glyph->t0;
        float s1 = glyph->s1;
        float t1 = glyph->t1;
        GLuint index = buffer->vertices->size;
        GLuint indices[] = {index, index+1, index+2,
                            index, index+2, index+3};
        vertex_t vertices[] = {
            { static_cast<float>(x0),y0,0,  s0,t0,  fg_color_1 },
            { static_cast<float>(x0),y1,0,  s0,t1,  fg_color_2 },
            { static_cast<float>(x1),y1,0,  s1,t1,  fg_color_2 },
            { static_cast<float>(x1),y0,0,  s1,t0,  fg_color_1 } };
        vertex_buffer_push_back_indices( buffer, indices, 6 );
        vertex_buffer_push_back_vertices( buffer, vertices, 4 );
        pen.x += glyph->advance_x;
    }
}

int main(void) {  
    GLFWwindow* window;
    
    const int width=640, height=480;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, "Moomin", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    glfwSetWindowSizeCallback(window, reshape);


    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf( stderr, "Error: %s\n", glewGetErrorString(err) );
        exit( EXIT_FAILURE );
    }
    

    atlas = texture_atlas_new( 1024, 1024, 1 );
    buffer = vertex_buffer_new( "vertex:3f,tex_coord:2f,color:4f" ); 
    texture_font_t *font =
        texture_font_new_from_file( atlas, 128, "lib/freetype-gl/fonts/ObelixPro.ttf" );

    vec2 pen    = {{50, 50}};
    vec4 black  = {{0.0, 0.0, 0.0, 1.0}};
    vec4 yellow = {{1.0, 1.0, 0.0, 1.0}};
    vec4 orange1 = {{1.0, 0.9, 0.0, 1.0}};
    vec4 orange2 = {{1.0, 0.6, 0.0, 1.0}};


    font->outline_type = 2;
    font->outline_thickness = 7;
    add_text( buffer, font, L"Freetype GL", pen, black, black );

    font->outline_type = 2;
    font->outline_thickness = 5;
    add_text( buffer, font, L"Freetype GL", pen, yellow, yellow );

    font->outline_type = 1;
    font->outline_thickness = 3;
    add_text( buffer, font, L"Freetype GL", pen, black, black );

    font->outline_type = 0;
    font->outline_thickness = 0;
    add_text( buffer, font, L"Freetype GL", pen, orange1, orange2 );

    shader = shader_load("lib/freetype-gl/shaders/v3f-t2f-c4f.vert",
                         "lib/freetype-gl/shaders/v3f-t2f-c4f.frag");
    mat4_set_identity( &projection );
    mat4_set_identity( &model );
    mat4_set_identity( &view );




    reshape(window, width, height);

    Renderer r = Renderer();
    Mesh squareMesh 
    {
        -10.0, 10.0,
        -10.0,-10.0,
         10.0, 10.0,
         10.0,-10.0
    };
    Entity e = Entity(320, 240, squareMesh);
    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.109803922, 0.109803922, 0.109803922, 1.0);

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        //r.draw(e);
        drawText();
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
