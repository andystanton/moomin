#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include <cmath>
#include <string>
#include <map>

#include <stdio.h>
#include <wchar.h>

#include <freetype-gl.h>
#include <GLFW/glfw3.h>

using std::string;
using std::wstring;
using std::map;
using std::make_pair;

void reshape(GLFWwindow* window, int width, int height) 
{
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION );
    glLoadIdentity();
    glScalef(1.0, -1.0, 1.0);
    glOrtho(0, width, height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(void) 
{  
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
        fprintf( stderr, "Error: %s\n", glewGetErrorString(err) );
        exit( EXIT_FAILURE );
    }
    

    EntityRenderer er = EntityRenderer();
    FreeTypeRenderer fr = FreeTypeRenderer();

    reshape(window, width, height);

    fr.reshapeEvent(width*2, height*2);

    // create something to draw
    Mesh squareMesh 
    {
        -10.0, 10.0,
        -10.0,-10.0,
         10.0, 10.0,
         10.0,-10.0
    };
    Entity e = Entity(320, 240, squareMesh);

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.109803922, 0.109803922, 0.109803922, 1.0);

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        er.draw(e);

        fr.drawText( "some text", 350, 650, FreeTypeRenderer::Font::ObelixPro, FreeTypeRenderer::Colour::GREEN );
        fr.drawText( "more text",   0,   0, FreeTypeRenderer::Font::Vera, FreeTypeRenderer::Colour::RED );

        fr.draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
