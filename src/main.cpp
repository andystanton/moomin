#include <iostream>

#include "drawing/GLFWGLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include "model/rules/DirectionAccelerationRule.h"
#include "model/rules/EntityAccelerationRule.h"
#include "model/rules/PositionAccelerationRule.h"
#include "model/rules/BoundingRule.h"
#include "model/rules/CollisionRule.h"
#include "model/PhysicsSystem.h"
#include "model/StandardPhysicsSystem.h"
#include "model/PhysicsHelper.h"


using namespace std;

int main(void)
{
    int width = 800, height = 600;

    // Create Physics System
    StandardPhysicsSystem physicsSystem(10 * width, 10 * height);
    PhysicsHelper physicsHelper(physicsSystem);

    // Initialise Graphics System
    GLFWGLHandler glHandler("Moomin Engine v1.0", width, height, &physicsHelper);

    // Create Renderers
    EntityRenderer er(physicsSystem.getEntities());
    FreeTypeRenderer fr = FreeTypeRenderer();

    // Register Renderers with Graphics System
    glHandler.setEntityRenderer(&er);
    glHandler.setFreeTypeRenderer(&fr);

    // Moomin!
    float lastUpdate = glfwGetTime();
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
