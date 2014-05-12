#include <iostream>

#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include "model/rules/DirectionAccelerationRule.h"
#include "model/rules/BoundingRule.h"
#include "model/rules/CollisionRule.h"
#include "model/rules/EntityAccelerationRule.h"
#include "model/PhysicsSystem.h"
#include "model/Circle.h"
#include "model/AABB.h"

using namespace std;

int width = 640, height = 640;

int worldWidth = 6400, worldHeight = 6400;

Circle * createRandomCircle()
{
    Circle * c = new Circle(rand() % worldWidth, 800 + (rand() % 4800), (rand() % 20) + 20);
    c->getVelocity().setX((rand() % 30) - 15);
    c->getVelocity().setY(rand() % 30);
    return c;
}

AABB * createRandomAABB()
{
    AABB * aabb = new AABB(rand() % worldWidth, 800 + (rand() % 4800), (rand() % 40) + 40, (rand() % 40) + 40);
    aabb->getVelocity().setX((rand() % 30) - 15);
    aabb->getVelocity().setY(rand() % 30);
    return aabb;
}

int main(void) 
{  
    // Create Physics System
    PhysicsSystem physicsSystem;

    // Create Rules
    DirectionAccelerationRule gravity(Vec2(0.f, -20.f));
    BoundingRule area(0.55f, Vec2(0.f, 0.f), Vec2(worldWidth, worldHeight));
    CollisionRule collisions(physicsSystem.getEntities());
    EntityAccelerationRule attraction(physicsSystem.getEntities());

    // Register Rules with Physics System
    //physicsSystem.addRule(&gravity);
    physicsSystem.addRule(&area);
    physicsSystem.addRule(&collisions);
    //physicsSystem.addRule(&attraction);

    AABB * aabb1 = new AABB(2000.f, 600.f, 200.f, 200.f);
    AABB * aabb2 = new AABB(2500.f, 1000.f, 200.f, 200.f);
    AABB * aabb3 = new AABB(3000.f, 600.f, 200.f, 200.f);

    aabb1->getVelocity().setX(10);
    aabb1->getVelocity().setY(10);

    aabb3->getVelocity().setX(-10);

    physicsSystem.addEntity(aabb1);
    physicsSystem.addEntity(aabb2);
    //physicsSystem.addEntity(aabb3);

    for (int i=0; i < 50; i++)
    {
        //physicsSystem.addEntity(createRandomCircle());
        //physicsSystem.addEntity(createRandomAABB());
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

            cout << "aabb1 velocity: " << aabb1->getVelocity().getX() << ", " << aabb1->getVelocity().getY() << endl;
            cout << "aabb2 velocity: " << aabb2->getVelocity().getX() << ", " << aabb2->getVelocity().getY() << endl;
        }
    }
    
    GLHandler::quit();
    return 0;
}
