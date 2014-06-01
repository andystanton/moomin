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

    void togglePause();
private:
    StandardPhysicsSystem & physicsSystem;
};

#endif
