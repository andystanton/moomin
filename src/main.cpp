#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include "drawing/Text.h"
#include "drawing/FontProvider.h"

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
    Mesh squareMesh 
    {
        -10.0, 10.0,
        -10.0,-10.0,
         10.0, 10.0,
         10.0,-10.0
    };

    Mesh hexMesh
    {
      0.0, 0.0,  0.0, 10.0,  1.74, 9.85,
      0.0, 0.0,  1.74, 9.85,  3.42, 9.4,
      0.0, 0.0,  3.42, 9.4,  5.0, 8.66,
      0.0, 0.0,  5.0, 8.66,  6.43, 7.66,
      0.0, 0.0,  6.43, 7.66,  7.66, 6.43,
      0.0, 0.0,  7.66, 6.43,  8.66, 5.0,
      0.0, 0.0,  8.66, 5.0,  9.4, 3.42,
      0.0, 0.0,  9.4, 3.42,  9.85, 1.74,
      0.0, 0.0,  9.85, 1.74,  10.0, 0.0,
      0.0, 0.0,  10.0, 0.0,  9.85, -1.74,
      0.0, 0.0,  9.85, -1.74,  9.4, -3.42,
      0.0, 0.0,  9.4, -3.42,  8.66, -5.0,
      0.0, 0.0,  8.66, -5.0,  7.66, -6.43,
      0.0, 0.0,  7.66, -6.43,  6.43, -7.66,
      0.0, 0.0,  6.43, -7.66,  5.0, -8.66,
      0.0, 0.0,  5.0, -8.66,  3.42, -9.4,
      0.0, 0.0,  3.42, -9.4,  1.74, -9.85,
      0.0, 0.0,  1.74, -9.85,  0.0, -10.0,
      0.0, 0.0,  0.0, -10.0,  -1.74, -9.85,
      0.0, 0.0,  -1.74, -9.85,  -3.42, -9.4,
      0.0, 0.0,  -3.42, -9.4,  -5.0, -8.66,
      0.0, 0.0,  -5.0, -8.66,  -6.43, -7.66,
      0.0, 0.0,  -6.43, -7.66,  -7.66, -6.43,
      0.0, 0.0,  -7.66, -6.43,  -8.66, -5.0,
      0.0, 0.0,  -8.66, -5.0,  -9.4, -3.42,
      0.0, 0.0,  -9.4, -3.42,  -9.85, -1.74,
      0.0, 0.0,  -9.85, -1.74,  -10.0, 0.0,
      0.0, 0.0,  -10.0, 0.0,  -9.85, 1.74,
      0.0, 0.0,  -9.85, 1.74,  -9.4, 3.42,
      0.0, 0.0,  -9.4, 3.42,  -8.66, 5.0,
      0.0, 0.0,  -8.66, 5.0,  -7.66, 6.43,
      0.0, 0.0,  -7.66, 6.43,  -6.43, 7.66,
      0.0, 0.0,  -6.43, 7.66,  -5.0, 8.66,
      0.0, 0.0,  -5.0, 8.66,  -3.42, 9.4,
      0.0, 0.0,  -3.42, 9.4,  -1.74, 9.85,
      0.0, 0.0,  -1.74, 9.85,  0.0, 10.0
    };

    //hexMesh.setType(Mesh::MeshType::fan);

    //Entity e = Entity(320, 240, squareMesh);
    Entity e = Entity(320, 240, hexMesh);
    entities->push_back(&e);

    while (GLHandler::isActive()) 
    {
        GLHandler::draw();
    }
    
    GLHandler::quit();
    return 0;
}
