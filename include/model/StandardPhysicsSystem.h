#ifndef _MOOMIN_STANDARD_PHYSICS_SYSTEM
#define _MOOMIN_STANDARD_PHYSICS_SYSTEM

#include "model/PhysicsSystem.h"

#include "model/rules/EntityAccelerationRule.h"
#include "model/rules/DirectionAccelerationRule.h"
#include "model/rules/PositionAccelerationRule.h"
#include "model/rules/BoundingRule.h"
#include "model/rules/CollisionRule.h"

class StandardPhysicsSystem
    : public PhysicsSystem
{
public:
    StandardPhysicsSystem(float width, float height);
    ~StandardPhysicsSystem();

    PositionAccelerationRule & singularity();
    EntityAccelerationRule & attraction();
    DirectionAccelerationRule & gravity();

    int getWidth();
    int getHeight();

    void resize(float width, float height);

private:
    int width, height;

    BoundingRule ruleBounding;
    CollisionRule ruleCollision;

    DirectionAccelerationRule ruleGravity;
    PositionAccelerationRule ruleSingularity;
    EntityAccelerationRule ruleAttraction;

    void addRule(Rule *);
    const set<Rule *> & getRules() const;
};

#endif
