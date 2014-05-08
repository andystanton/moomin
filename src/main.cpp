#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include "model/rules/AccelerationRule.h"
#include "model/rules/BoundingRule.h"
#include "model/rules/CollisionDetectionRule.h"
#include "model/PhysicsSystem.h"
#include "model/Circle.h"

using namespace std;

int main(void) 
{  
    // Create Physics System
    PhysicsSystem physicsSystem;

    // Create Rules
    AccelerationRule gravity(Vec2(0.f, -0.1f));
    BoundingRule area(0.55f, Vec2(0.f, 0.f), Vec2(640.f, 480.f));
    CollisionDetectionRule collisions(physicsSystem.getEntities());

    // Register Rules with Physics System
    physicsSystem.addRule(&gravity);
    physicsSystem.addRule(&area);
    physicsSystem.addRule(&collisions);


    // Create Entities
    Circle c1 = Circle(328, 400, 10);
    Circle c2 = Circle(320, 300, 10);
    Circle c3 = Circle(400, 480, 10);
    Circle c4 = Circle(200, 480, 10);
    Circle c5 = Circle(100, 50, 10);

    c4.getVelocity().setX(5.f);
    c4.getVelocity().setY(2.f);

    c5.getVelocity().setX(-5.f);
    c5.getVelocity().setY(0.4f);

    // Register Entities with Physics System
    physicsSystem.addEntity(&c1);
    physicsSystem.addEntity(&c2);
    physicsSystem.addEntity(&c3);
    physicsSystem.addEntity(&c4);
    physicsSystem.addEntity(&c5);



    // Initialise Graphics System
    GLHandler::init("Moomin Engine v1.0", 640, 480);

    // Create Renderers
    EntityRenderer er(physicsSystem.getEntities());
    FreeTypeRenderer fr = FreeTypeRenderer();

    // Register Renderers with Graphics System
    GLHandler::registerRenderer(&er);
    GLHandler::setFreeTypeRenderer(&fr);


    // Moomin!
    while (GLHandler::isActive()) 
    {
        GLHandler::draw();
        physicsSystem.step(glfwGetTime() * 1000);
    }
    
    GLHandler::quit();
    return 0;
}
