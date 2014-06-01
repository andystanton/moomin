#ifndef _MOOMIN_PHYSICS_HELPER
#define _MOOMIN_PHYSICS_HELPER

#include "model/StandardPhysicsSystem.h"

class PhysicsHelper
{
public:
    PhysicsHelper(StandardPhysicsSystem &);
    ~PhysicsHelper();

    void enablePositionAccelerationRule(bool inverted);
    void enableEntityAccelerationRule(bool inverted);
    void enableDirectionAccelerationRule(char direction);
    void disableAccelerationRules();

    void addCircle(Vec2 pos, float radius, Vec2 velocity = Vec2(0.f, 0.f));
    void addAABB(Vec2 pos, Vec2 bounds, Vec2 velocity = Vec2(0.f, 0.f));

    void addCircleRandom();
    void addAABBRandom();

    void addCirclesRandom(int count = 50);
    void addAABBsRandom(int count = 50);

    void addCirclesLattice(Vec2 pos, Vec2 dimensions, int divisions, Vec2 velocity = Vec2(0,0));
    void addAABBsLattice(Vec2 pos, Vec2 dimensions, int divisions, Vec2 velocity = Vec2(0,0));

    void addCirclesLatticeCentre(Vec2 dimensions, int divisions);
    void addAABBsLatticeCentre(Vec2 dimensions, int divisions);

    void addChaosLattice(bool inverted);

    void togglePause();
private:
    StandardPhysicsSystem & physicsSystem;
};

#endif
