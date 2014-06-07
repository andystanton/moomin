#include "drawing/GLHandler.hpp"
#include "model/PhysicsHelper.hpp"

using namespace std;

int main( void )
{
    int width = 600, height = 400;
    int worldWidth = 6000, worldHeight = 4000;

    // Create Physics System
    PhysicsHelper physicsHelper(worldWidth, worldHeight);

    // Initialise Graphics System
    GLHandler glHandler("Moomin Engine v1.0", width, height, physicsHelper);

    // Moomin!
    float lastUpdate = glHandler.getTime();
    while (glHandler.isActive())
    {
        glHandler.draw();

        float time = glHandler.getTime();
        physicsHelper.step(time - lastUpdate);
        lastUpdate = time;
    }

    glHandler.quit();

    return 0;
}
