#ifndef _MOOMIN_POSITION_ACCELERATION_RULE
#define _MOOMIN_POSITION_ACCELERATION_RULE

#include "model/Rule.h"
#include "core/Vec2.h"

class PositionAccelerationRule
    : public Rule
{
public:
    PositionAccelerationRule(const Vec2 &, float);
    ~PositionAccelerationRule();

    Vec2 & getOrigin();
    void apply(Entity &, float delta);
    void setInverted(bool);
    float getAcceleration();
private:
    Vec2 origin;
    float acceleration;
    int directionScale;
};

#endif
