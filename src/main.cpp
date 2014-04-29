#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include "model/Circle.h"

using namespace std;

int main(void) 
{  
    GLHandler::init("Moomin Engine v1.0", 640, 480);

    vector<Entity *> * entities = new vector<Entity *>();

    EntityRenderer er = EntityRenderer(entities);
    FreeTypeRenderer fr = FreeTypeRenderer();

    GLHandler::registerRenderer(&er);
    GLHandler::setFreeTypeRenderer(&fr);

    // create something to draw
    Mesh squareMesh = Mesh(
        Mesh::MeshType::quads,
        {
            -10.0, 10.0,
            -10.0,-10.0,
             10.0, 10.0,
             10.0,-10.0
        }
    );
    
    Entity e = Entity(320, 240, squareMesh);
    entities->push_back(&e);

    Circle c = Circle(400, 300);
    entities->push_back(&c);

    while (GLHandler::isActive()) 
    {
        GLHandler::draw();
    }
    
    GLHandler::quit();
    return 0;
}
