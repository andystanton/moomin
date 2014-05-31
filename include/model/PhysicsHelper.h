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

    void togglePause();
private:
    StandardPhysicsSystem & physicsSystem;
};

#endif
