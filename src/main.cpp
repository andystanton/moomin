#include <cmath>
#include <string>
#include <map>

#include <iostream>

#include <stdio.h>
#include <wchar.h>

#include <freetype-gl.h>
#include <GLFW/glfw3.h>

#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"



int main(void) 
{  
    GLHandler::init();

    vector<Entity *> * entities = new vector<Entity *>();

    EntityRenderer er = EntityRenderer(entities);
    FreeTypeRenderer fr = FreeTypeRenderer();

    // create something to draw
    Mesh squareMesh 
    {
        -10.0, 10.0,
        -10.0,-10.0,
         10.0, 10.0,
         10.0,-10.0
    };
    Entity e = Entity(320, 240, squareMesh);    
    entities->push_back(&e);

    GLHandler::registerRenderer(&er);
    GLHandler::registerRenderer(&fr);

    while (!glfwWindowShouldClose(GLHandler::window)) 
    {
        fr.drawText("some text", 350, 650, FreeTypeRenderer::Font::ObelixPro, FreeTypeRenderer::Colour::GREEN);
        fr.drawText("more text",   0,   0, FreeTypeRenderer::Font::Vera, FreeTypeRenderer::Colour::RED);
        GLHandler::draw();
    }
    
    glfwTerminate();
    return 0;
}
