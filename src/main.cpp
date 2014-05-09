#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include "model/rules/AccelerationRule.h"
#include "model/rules/BoundingRule.h"
#include "model/rules/CollisionRule.h"
#include "model/PhysicsSystem.h"
#include "model/Circle.h"

using namespace std;

int width = 640, height = 640;

Circle * createRandomCircle()
{
    Circle * c = new Circle(rand() % width, rand() % height, (rand() % 30) + 10);
    c->getVelocity().setX(rand() % 3);
    c->getVelocity().setY(rand() % 3);
    return c;
}

int main(void) 
{  
    // Create Physics System
    PhysicsSystem physicsSystem;

    // Create Rules
    AccelerationRule gravity(Vec2(0.f, -20.f));
    BoundingRule area(0.55f, Vec2(0.f, 0.f), Vec2(width, height));
    CollisionRule collisions(physicsSystem.getEntities());

    // Register Rules with Physics System
    physicsSystem.addRule(&gravity);
    physicsSystem.addRule(&area);
    physicsSystem.addRule(&collisions);


    // for (int i=0; i < 15; i++)
    // {
    //     physicsSystem.addEntity(createRandomCircle());
    // }

    physicsSystem.addEntity(new Circle(320, 400, 10));


    // Initialise Graphics System
    GLHandler::init("Moomin Engine v1.0", width, height);

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
        if (GLHandler::isPhysics())
        {
            physicsSystem.step((glfwGetTime() - lastUpdate) * 1000);
            lastUpdate = glfwGetTime();
        }
    }
    
    GLHandler::quit();
    return 0;
}
