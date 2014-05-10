#ifndef _MOOMIN_ACCELERATION_RULE
#define _MOOMIN_ACCELERATION_RULE

#include "model/Rule.h"
#include "core/Vec2.h"

class DirectionAccelerationRule
    : public Rule
{
public:
    DirectionAccelerationRule(const Vec2&);
    ~DirectionAccelerationRule();

    const Vec2& getAcceleration();
    void apply(Entity&, float delta);
private:
    Vec2 acceleration;
};

#endif