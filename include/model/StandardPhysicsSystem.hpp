#ifndef _MOOMIN_STANDARD_PHYSICS_SYSTEM
#define _MOOMIN_STANDARD_PHYSICS_SYSTEM

#include "model/PhysicsSystem.hpp"

#include "model/rules/EntityAccelerationRule.hpp"
#include "model/rules/DirectionAccelerationRule.hpp"
#include "model/rules/PositionAccelerationRule.hpp"
#include "model/rules/BoundingRule.hpp"
#include "model/rules/CollisionRule.hpp"

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
