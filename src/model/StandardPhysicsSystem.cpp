#include "model/StandardPhysicsSystem.h"

StandardPhysicsSystem::StandardPhysicsSystem(float width, float height)
    : PhysicsSystem()
    , width(width)
    , height(height)
    , ruleBounding(0.55f, Vec2(0.f, 0.f), Vec2(width, height))
    , ruleCollision(entities)
    , ruleGravity(Vec2(0.f, -20.f))
    , ruleSingularity(Vec2(width/2, height/2), 20.f)
    , ruleAttraction(entities, 1.f)
{
    ruleGravity.setEnabled(false);
    ruleSingularity.setEnabled(false);
    ruleAttraction.setEnabled(false);

    PhysicsSystem::addRule(&ruleBounding);
    PhysicsSystem::addRule(&ruleCollision);
    PhysicsSystem::addRule(&ruleGravity);
    PhysicsSystem::addRule(&ruleSingularity);
    PhysicsSystem::addRule(&ruleAttraction);
}

StandardPhysicsSystem::~StandardPhysicsSystem()
{

}

PositionAccelerationRule & StandardPhysicsSystem::singularity()
{
    return ruleSingularity;
}

EntityAccelerationRule & StandardPhysicsSystem::attraction()
{
    return ruleAttraction;
}

DirectionAccelerationRule & StandardPhysicsSystem::gravity()
{
    return ruleGravity;
}

int StandardPhysicsSystem::getWidth()
{
    return width;
}

int StandardPhysicsSystem::getHeight()
{
    return height;
}
