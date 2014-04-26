#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include "drawing/Text.h"
#include "drawing/FontProvider.h"

using namespace std;

int main(void) 
{  
    GLHandler::init("Moomin Engine v1.0");

    vector<Entity *> * entities = new vector<Entity *>();

    EntityRenderer er = EntityRenderer(entities);
    FreeTypeRenderer fr = FreeTypeRenderer();

    GLHandler::registerRenderer(&er);
    GLHandler::setFreeTypeRenderer(&fr);

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

    while (GLHandler::isActive()) 
    {
        GLHandler::draw();
    }
    
    GLHandler::quit();
    return 0;
}
