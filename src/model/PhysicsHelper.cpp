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
            acceleration.setX(0.f);
            acceleration.setY(magnitude);
            break;
        case 'S':
            acceleration.setX(0.f);
            acceleration.setY(-magnitude);
            break;
        case 'E':
            acceleration.setX(magnitude);
            acceleration.setY(0.f);
            break;
        case 'W':
            acceleration.setX(-magnitude);
            acceleration.setY(0.f);
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
