#include "drawing/GLHandler.hpp"
#include "drawing/EntityRenderer.hpp"

#include "model/StandardPhysicsSystem.hpp"
#include "model/PhysicsHelper.hpp"

using namespace std;



int main( void )
{
    int width = 600, height = 400;

    // Create Physics System
    StandardPhysicsSystem physicsSystem(width * 10, height * 10);
    PhysicsHelper physicsHelper(physicsSystem);

    // Initialise Graphics System
    GLHandler glHandler("Moomin Engine v1.0", width, height, physicsHelper);

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
