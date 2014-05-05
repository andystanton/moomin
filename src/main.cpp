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

    Circle c = Circle(320, 400, 10);

    AccelerationRule gravity(Vec2(0.f, -0.1f));
    BoundingRule area(0.55f, Vec2(0.f, 0.f), Vec2(640.f, 480.f));

    PhysicsSystem physicsSystem;

    physicsSystem.addEntity(&c);

    physicsSystem.addRule(&gravity);
    physicsSystem.addRule(&area);

    EntityRenderer er(physicsSystem.getEntities());
    FreeTypeRenderer fr = FreeTypeRenderer();

    GLHandler::registerRenderer(&er);
    GLHandler::setFreeTypeRenderer(&fr);

    while (GLHandler::isActive()) 
    {
        GLHandler::draw();
        physicsSystem.step(glfwGetTime() * 1000);
    }
    
    GLHandler::quit();
    return 0;
}
