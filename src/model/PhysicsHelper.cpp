#include "model/PhysicsHelper.hpp"

PhysicsHelper::PhysicsHelper(StandardPhysicsSystem & physicsSystem)
    : physicsSystem(physicsSystem)
    , spawnMode(Entity::CollisionType::circle)
{
    addCirclesLatticeCentre();
}

PhysicsHelper::~PhysicsHelper()
{

}

const set<Entity *>& PhysicsHelper::getEntities()
{
    return physicsSystem.getEntities();
}

int PhysicsHelper::getWidth()
{
    return physicsSystem.getWidth();
}

int PhysicsHelper::getHeight()
{
    return physicsSystem.getHeight();
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

void PhysicsHelper::addCircleRandom(Vec2 velocity)
{
    int worldWidth = (int) physicsSystem.getWidth();
    int worldHeight = (int) physicsSystem.getHeight();

    Vec2 pos(rand() % worldWidth, worldHeight/8 + (rand() % (worldHeight * 3 / 4)));
    float radius = (rand() % 20) + 20;

    if (velocity == Vec2::ORIGIN) velocity = Vec2((rand() % 30) - 15, rand() % 30);

    addCircle(pos, radius, velocity);
}

void PhysicsHelper::addAABBRandom(Vec2 velocity)
{
    int worldWidth = (int) physicsSystem.getWidth();
    int worldHeight = (int) physicsSystem.getHeight();

    Vec2 pos(rand() % worldWidth, worldHeight/8 + (rand() % (worldHeight * 3 / 4)));
    Vec2 bounding((rand() % 160) + 80, (rand() % 160) + 80);

    if (velocity == Vec2::ORIGIN) velocity = Vec2((rand() % 30) - 15, rand() % 30);

    addAABB(pos, bounding, velocity);
}

void PhysicsHelper::addCirclesRandom(int count)
{
    physicsSystem.clearEntities();

    for (int i=0; i < count; i++)
    {
        addCircleRandom();
    }
}

void PhysicsHelper::addAABBsRandom(int count)
{
    physicsSystem.clearEntities();

    for (int i=0; i < count; i++)
    {
        addAABBRandom();
    }
}

void PhysicsHelper::addCirclesLattice(Vec2 pos, Vec2 dimensions, int divisions, Vec2 velocity)
{
    float diameter = dimensions.getX() / divisions;
    float radius = diameter / 2;
    float x = pos.getX() + radius;
    float y = pos.getY() + radius;
    for (int i=0; i < divisions; i++)
    {
        for (int j=0; j < divisions; j++)
        {
            addCircle(Vec2(x + i * diameter, y + j * diameter), radius, velocity);
        }
    }
}

void PhysicsHelper::addAABBsLattice(Vec2 pos, Vec2 dimensions, int divisions, Vec2 velocity)
{
    float width = dimensions.getX() / divisions;
    float height = dimensions.getY() / divisions;
    float x = pos.getX() + height/2;
    float y = pos.getY() + width/2;
    for (int i=0; i < 10; i++)
    {
        for (int j=0; j < 10; j++)
        {
            addAABB(Vec2(x + i * width, y + j * height), Vec2(width, height), velocity);
        }
    }
}

void PhysicsHelper::addCirclesLatticeCentre(int divisions)
{
    physicsSystem.clearEntities();
    float latticeWidth = physicsSystem.getWidth() / 8;
    float halfWidth = (physicsSystem.getWidth() -latticeWidth) / 2;
    float halfHeight = (physicsSystem.getHeight() -latticeWidth) / 2;
    addCirclesLattice(Vec2(halfWidth, halfHeight), Vec2(latticeWidth, latticeWidth), divisions);
}

void PhysicsHelper::addAABBsLatticeCentre(int divisions)
{
    physicsSystem.clearEntities();
    float latticeWidth = physicsSystem.getWidth() / 8;
    float halfWidth = (physicsSystem.getWidth() - latticeWidth - (latticeWidth / divisions)) / 2;
    float halfHeight = (physicsSystem.getHeight() - latticeWidth - (latticeWidth / divisions)) / 2;
    addAABBsLattice(Vec2(halfWidth, halfHeight), Vec2(latticeWidth, latticeWidth), divisions);
}

void PhysicsHelper::addChaosLattice(bool inverted, int divisions)
{
    physicsSystem.clearEntities();
    disableAccelerationRules();
    float speed = 30;

    float latticeWidth = physicsSystem.getWidth() / 8;
    float entitySize = latticeWidth / divisions;

    //float circleWidthOffset = physicsSystem.getWidth() - latticeWidth + entitySize / 2;
    float circleHeightOffset = physicsSystem.getHeight() - latticeWidth - (entitySize / 2);

    float aabbWidthOffset = physicsSystem.getWidth() - latticeWidth - entitySize;
    float aabbHeightOffset = physicsSystem.getHeight() - latticeWidth - entitySize;

    // TODO: make this less shit

    if (!inverted)
    {
        Vec2 circleCentre(entitySize + latticeWidth / 2, entitySize + latticeWidth / 2);
        Vec2 aabbCentre(aabbWidthOffset + latticeWidth / 2, aabbHeightOffset + latticeWidth / 2);

        Vec2 circleVelocity = Vec2(physicsSystem.getWidth(), physicsSystem.getHeight()) - circleCentre;
        circleVelocity.normalise();
        circleVelocity *= speed;
        circleVelocity.setX((int) circleVelocity.getX());
        circleVelocity.setY((int) circleVelocity.getY());

        Vec2 aabbVelocity = Vec2::ORIGIN - aabbCentre;
        aabbVelocity.normalise();
        aabbVelocity *= speed;
        aabbVelocity.setX((int) aabbVelocity.getX());
        aabbVelocity.setY((int) aabbVelocity.getY());

        addCirclesLattice(Vec2(entitySize * 1.5, entitySize * 1.5), Vec2(latticeWidth, latticeWidth), divisions, circleVelocity);
        addAABBsLattice(Vec2(aabbWidthOffset, aabbHeightOffset), Vec2(latticeWidth, latticeWidth), divisions, aabbVelocity);
    } else
    {
        Vec2 circleCentre(entitySize + latticeWidth / 2, aabbHeightOffset + latticeWidth / 2);
        Vec2 aabbCentre(aabbWidthOffset + latticeWidth / 2, entitySize + latticeWidth / 2);

        Vec2 circleVelocity = Vec2(physicsSystem.getWidth(), 0.f) - circleCentre;
        circleVelocity.normalise();
        circleVelocity *= speed;
        circleVelocity.setX((int) circleVelocity.getX());
        circleVelocity.setY((int) circleVelocity.getY());

        Vec2 aabbVelocity = Vec2(0.f, physicsSystem.getHeight()) - aabbCentre;
        aabbVelocity.normalise();
        aabbVelocity *= speed;
        aabbVelocity.setX((int) aabbVelocity.getX());
        aabbVelocity.setY((int) aabbVelocity.getY());

        addCirclesLattice(Vec2(entitySize * 1.5, circleHeightOffset), Vec2(latticeWidth, latticeWidth), divisions, circleVelocity);
        addAABBsLattice(Vec2(aabbWidthOffset, entitySize), Vec2(latticeWidth, latticeWidth), divisions, aabbVelocity);
    }
}

void PhysicsHelper::setSpawnModeCircle()
{
    spawnMode = Entity::CollisionType::circle;
}

void PhysicsHelper::setSpawnModeAABB()
{
    spawnMode = Entity::CollisionType::aabb;
}

void PhysicsHelper::spawnEntityOnTrajectory(Vec2 trajectoryStart, Vec2 trajectoryEnd)
{
    Vec2 pos(trajectoryStart.getX() * 10, getHeight() - (trajectoryStart.getY() * 10));
    Vec2 velocity(trajectoryEnd.getX() - trajectoryStart.getX(), -(trajectoryEnd.getY() - trajectoryStart.getY()));

    switch (spawnMode)
    {
        case Entity::CollisionType::aabb:
            addAABB(pos, Vec2((rand() % 20) + 50, (rand() % 20) + 50), velocity);
            break;
        case Entity::CollisionType::circle:
            addCircle(pos, (rand() % 20) + 20, velocity);
            break;
        case Entity::CollisionType::mock:
            break;
        default:
            break;
    }
}
