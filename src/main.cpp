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


using namespace std;

int width = 640, height = 640;

int worldWidth = 6400, worldHeight = 6400;

int main(void)
{
    // Create Physics System
    StandardPhysicsSystem stdPhysicsSystem(worldWidth, worldHeight);

    // Initialise Graphics System
    GLHandler::init("Moomin Engine v1.0", width, height);

    // Create Renderers
    EntityRenderer er(stdPhysicsSystem.getEntities());
    FreeTypeRenderer fr = FreeTypeRenderer();

    // Register Renderers with Graphics System
    GLHandler::setEntityRenderer(&er);
    GLHandler::setFreeTypeRenderer(&fr);

    GLHandler::registerPhysicsSystem(&stdPhysicsSystem);

    // Moomin!
    float lastUpdate = glfwGetTime();
    while (GLHandler::isActive())
    {
        GLHandler::draw();
        if (GLHandler::isPhysics())
        {
            stdPhysicsSystem.step((glfwGetTime() - lastUpdate) * 1000);
            lastUpdate = glfwGetTime();
        }
    }

    GLHandler::quit();
    return 0;
}
