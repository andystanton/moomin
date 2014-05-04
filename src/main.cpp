#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include "model/rules/AccelerationRule.h"
#include "model/rules/BoundingRule.h"
#include "model/PhysicsSystem.h"
#include "model/Circle.h"

using namespace std;

int main(void) 
{  
    GLHandler::init("Moomin Engine v1.0", 640, 480);

    // create something to draw
    Mesh squareMesh = Mesh(
        Mesh::MeshType::quads,
        {
            -10.0, 10.0,
            -10.0,-10.0,
             10.0, 10.0,
             10.0,-10.0
        }
    );
    
    Entity e = Entity(320, 240, squareMesh);
    //entities->push_back(&e);

    Circle c = Circle(400, 300, 10);
    //entities->push_back(&c);

    AccelerationRule gravity(Vec2(0.f, -0.1f));
    BoundingRule area(0.55f, Vec2(0.f, 0.f), Vec2(640.f, 480.f));

    float currentTime = glfwGetTime();

    PhysicsSystem physicsSystem;

    physicsSystem.addEntity(&c);
    physicsSystem.addEntity(&e);

    physicsSystem.addRule(&gravity);
    physicsSystem.addRule(&area);

    EntityRenderer er(physicsSystem.getEntities());
    FreeTypeRenderer fr = FreeTypeRenderer();

    GLHandler::registerRenderer(&er);
    GLHandler::setFreeTypeRenderer(&fr);

    while (GLHandler::isActive()) 
    {
        GLHandler::draw();

        physicsSystem.step(currentTime * 1000);

        for (auto entity : physicsSystem.getEntities())
        {
            Vec2& pos = entity->getPos();
            pos.setX(pos.getX() + entity->getVelocity().getX());
            pos.setY(pos.getY() + entity->getVelocity().getY());
            //cout << entity->getPos().getX() << ", " << entity->getPos().getY() << endl;
        }


        currentTime = glfwGetTime();
    }
    
    GLHandler::quit();
    return 0;
}
