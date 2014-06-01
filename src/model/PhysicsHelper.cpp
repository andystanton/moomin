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

void PhysicsHelper::addCircle(Vec2 pos, float radius, Vec2 velocity)
{
    physicsSystem.addEntity(new Circle(pos, radius, velocity));
}

void PhysicsHelper::addAABB(Vec2 pos, Vec2 bounds, Vec2 velocity)
{
    physicsSystem.addEntity(new AABB(pos, bounds, velocity));
}

void PhysicsHelper::addRandomCircle()
{
    int worldWidth = (int) physicsSystem.getWidth();
    int worldHeight = (int) physicsSystem.getHeight();

    Vec2 pos(rand() % worldWidth, worldHeight/8 + (rand() % (worldHeight * 3 / 4)));
    float radius = (rand() % 20) + 20;
    Vec2 velocity((rand() % 30) - 15, rand() % 30);

    addCircle(pos, radius, velocity);
}

void PhysicsHelper::addRandomAABB()
{
    int worldWidth = (int) physicsSystem.getWidth();
    int worldHeight = (int) physicsSystem.getHeight();

    Vec2 pos(rand() % worldWidth, worldHeight/8 + (rand() % (worldHeight * 3 / 4)));
    Vec2 bounding((rand() % 160) + 80, (rand() % 160) + 80);
    Vec2 velocity((rand() % 30) - 15, rand() % 30);

    addAABB(pos, bounding, velocity);
}
