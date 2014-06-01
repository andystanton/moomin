#include <iostream>

#include "drawing/GLHandler.h"
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

int width = 640, height = 640;

int worldWidth = width * 10, worldHeight = height * 10;

int main(void)
{
    // Create Physics System
    StandardPhysicsSystem physicsSystem(worldWidth, worldHeight);
    PhysicsHelper physicsHelper(physicsSystem);

    // Initialise Graphics System
    GLHandler::init("Moomin Engine v1.0", width, height, &physicsHelper);

    // Create Renderers
    EntityRenderer er(physicsSystem.getEntities());
    FreeTypeRenderer fr = FreeTypeRenderer();

    // Register Renderers with Graphics System
    GLHandler::setEntityRenderer(&er);
    GLHandler::setFreeTypeRenderer(&fr);

    // Moomin!
    float lastUpdate = glfwGetTime();
    while (GLHandler::isActive())
    {
        GLHandler::draw();
        physicsSystem.step((glfwGetTime() - lastUpdate) * 1000);
        lastUpdate = glfwGetTime();
    }

    GLHandler::quit();
    return 0;
}
