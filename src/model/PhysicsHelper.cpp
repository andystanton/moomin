#include "model/PhysicsHelper.h"

PhysicsHelper::PhysicsHelper(StandardPhysicsSystem & physicsSystem)
    : physicsSystem(physicsSystem)
{

}

PhysicsHelper::~PhysicsHelper()
{

}

void PhysicsHelper::enablePositionAccelerationRule(bool inverted)
{
    physicsSystem.gravity().setEnabled(false);
    physicsSystem.attraction().setEnabled(false);

    PositionAccelerationRule & singularity = physicsSystem.singularity();
    if (!inverted) singularity.setInverted(false);
    if (inverted) singularity.setInverted(true);
    singularity.setEnabled(true);
}

void PhysicsHelper::enableEntityAccelerationRule(bool inverted)
{
    physicsSystem.gravity().setEnabled(false);
    physicsSystem.singularity().setEnabled(false);

    EntityAccelerationRule & attraction = physicsSystem.attraction();
    if (!inverted) attraction.setInverted(false);
    if (inverted) attraction.setInverted(true);
    attraction.setEnabled(true);
}

void PhysicsHelper::enableDirectionAccelerationRule(char direction)
{
    physicsSystem.attraction().setEnabled(false);
    physicsSystem.singularity().setEnabled(false);

    DirectionAccelerationRule & gravity = physicsSystem.gravity();
    Vec2 & acceleration = gravity.getAcceleration();
    float magnitude = acceleration.getMagnitude();
    switch (direction)
    {
        case 'N':
            acceleration = Vec2(0.f, magnitude);
            break;
        case 'S':
            acceleration = Vec2(0.f, -magnitude);
            break;
        case 'E':
            acceleration = Vec2(magnitude, 0.f);
            break;
        case 'W':
            acceleration = Vec2(-magnitude, 0.f);
            break;
    }
    gravity.setEnabled(true);
}

void PhysicsHelper::disableAccelerationRules()
{
    physicsSystem.gravity().setEnabled(false);
    physicsSystem.singularity().setEnabled(false);
    physicsSystem.attraction().setEnabled(false);
}

void PhysicsHelper::togglePause()
{
    physicsSystem.setPaused(!physicsSystem.isPaused());
}
