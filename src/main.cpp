#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include "model/rules/DirectionAccelerationRule.h"
#include "model/rules/BoundingRule.h"
#include "model/rules/CollisionRule.h"
#include "model/rules/GravityRule.h"
#include "model/PhysicsSystem.h"
#include "model/Circle.h"

using namespace std;

int width = 640, height = 640;

Circle * createRandomCircle()
{
    Circle * c = new Circle(800 + (rand() % 4800), 800 + (rand() % 4800), (rand() % 20) + 20);
    c->getVelocity().setX(rand() % 3);
    c->getVelocity().setY(rand() % 3);
    return c;
}

int main(void) 
{  
    // Create Physics System
    PhysicsSystem physicsSystem;

    // Create Rules
    DirectionAccelerationRule gravity(Vec2(0.f, -20.f));
    BoundingRule area(0.55f, Vec2(0.f, 0.f), Vec2(6400, 6400));
    CollisionRule collisions(physicsSystem.getEntities());
    GravityRule attraction(physicsSystem.getEntities());

    // Register Rules with Physics System
    //physicsSystem.addRule(&gravity);
    physicsSystem.addRule(&area);
    physicsSystem.addRule(&collisions);
    physicsSystem.addRule(&attraction);


    for (int i=0; i < 50; i++)
    {
        physicsSystem.addEntity(createRandomCircle());
    }

    // physicsSystem.addEntity(new Circle(320, 400, 10));
    // physicsSystem.addEntity(new Circle(320, 300, 10));


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
