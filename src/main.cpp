#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"

#include "model/StandardPhysicsSystem.h"
#include "model/PhysicsHelper.h"

using namespace std;



int main( void )
{
    int width = 800, height = 600;

    // Create Physics System
    StandardPhysicsSystem physicsSystem(width * 10, height * 10);
    PhysicsHelper physicsHelper(physicsSystem);

    // Initialise Graphics System
    GLHandler glHandler("Moomin Engine v1.0", width, height, physicsHelper);

    // Create Renderers
    EntityRenderer er(physicsSystem.getEntities());

    // Register Renderers with Graphics System
    glHandler.setEntityRenderer(&er);

    // Moomin!
    float lastUpdate = glHandler.getTime();
    while (glHandler.isActive())
    {
        glHandler.draw();

        float time = glHandler.getTime();
        physicsSystem.step(1000 * (time - lastUpdate));
        lastUpdate = time;
    }

    glHandler.quit();

    return 0;
}
