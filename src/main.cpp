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


using namespace std;

int width = 640, height = 640;

int worldWidth = 6400, worldHeight = 6400;

int main(void)
{
    // Create Physics System
    PhysicsSystem physicsSystem;

    // Create World Rules
    BoundingRule area(0.55f, Vec2(0.f, 0.f), Vec2(worldWidth, worldHeight));
    CollisionRule collisions(physicsSystem.getEntities());

    // Create Physics Rules
    DirectionAccelerationRule gravity(Vec2(0.f, -20.f));
    EntityAccelerationRule attraction(physicsSystem.getEntities(), 10.f);
    PositionAccelerationRule singularity(Vec2(worldWidth * 0.5, worldHeight * 0.5), 20.f);

    // Register Rules with Physics System
    physicsSystem.addRule(&area);
    physicsSystem.addRule(&collisions);
    physicsSystem.addRule(&gravity);
    physicsSystem.addRule(&attraction);
    physicsSystem.addRule(&singularity);

    // Disable all rules
    attraction.setEnabled(false);
    gravity.setEnabled(false);
    singularity.setEnabled(false);

    // Initialise Graphics System
    GLHandler::init("Moomin Engine v1.0", width, height);

    // Create Renderers
    EntityRenderer er(physicsSystem.getEntities());
    FreeTypeRenderer fr = FreeTypeRenderer();

    // Register Renderers with Graphics System
    GLHandler::setEntityRenderer(&er);
    GLHandler::setFreeTypeRenderer(&fr);

    GLHandler::registerPhysicsSystem(&physicsSystem);


    // Moomin!
    float lastUpdate = glfwGetTime();
    while (GLHandler::isActive())
    {
        GLHandler::draw();
        if (GLHandler::isPhysics())
        {
            physicsSystem.step((glfwGetTime() - lastUpdate) * 1000);
            lastUpdate = glfwGetTime();
        }
    }

    GLHandler::quit();
    return 0;
}
