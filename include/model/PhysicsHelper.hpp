#ifndef _MOOMIN_PHYSICS_HELPER
#define _MOOMIN_PHYSICS_HELPER

#include "model/StandardPhysicsSystem.hpp"

class PhysicsHelper
{
public:
    PhysicsHelper(StandardPhysicsSystem &);
    ~PhysicsHelper();

    set<Entity *> getEntities();

    int getWidth();
    int getHeight();

    void enablePositionAccelerationRule(bool inverted);
    void enableEntityAccelerationRule(bool inverted);
    void enableDirectionAccelerationRule(char direction);
    void disableAccelerationRules();

    void addCircle(Vec2 pos, float radius, Vec2 velocity = Vec2::ORIGIN);
    void addAABB(Vec2 pos, Vec2 bounds, Vec2 velocity = Vec2::ORIGIN);

    void addCircleRandom(Vec2 velocity = Vec2::ORIGIN);
    void addAABBRandom(Vec2 velocity = Vec2::ORIGIN);

    void addCirclesRandom(int count = 50);
    void addAABBsRandom(int count = 50);

    void addCirclesLattice(Vec2 pos, Vec2 dimensions, int divisions, Vec2 velocity = Vec2::ORIGIN);
    void addAABBsLattice(Vec2 pos, Vec2 dimensions, int divisions, Vec2 velocity = Vec2::ORIGIN);

    void addCirclesLatticeCentre(int divisions = 10);
    void addAABBsLatticeCentre(int divisions = 10);

    void addChaosLattice(bool inverted, int divisions = 10);

    void togglePause();

    void setSpawnModeCircle();
    void setSpawnModeAABB();

    void spawnEntityOnTrajectory(Vec2 trajectoryStart, Vec2 trajectoryEnd);
private:
    StandardPhysicsSystem & physicsSystem;
    Entity::CollisionType spawnMode;
};

#endif
