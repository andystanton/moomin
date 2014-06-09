#include "drawing/GLCoordinator.hpp"
#include "model/PhysicsHelper.hpp"

using namespace std;

int main(void)
{
    int width = 640, height = 400;
    int worldWidth = 6400, worldHeight = 4000;

    // Create Physics System
    PhysicsHelper physicsHelper(worldWidth, worldHeight);

    // Initialise Graphics System
    GLCoordinator glCoordinator("Moomin Engine v1.0", width, height, physicsHelper);

    // Moomin!
    float lastUpdate = glCoordinator.getTime();
    while (glCoordinator.isActive())
    {
        glCoordinator.draw();

        float time = glCoordinator.getTime();
        physicsHelper.step(time - lastUpdate);
        lastUpdate = time;
    }

    glCoordinator.quit();

    return 0;
}
