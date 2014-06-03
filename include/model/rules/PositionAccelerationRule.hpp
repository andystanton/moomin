#ifndef _MOOMIN_POSITION_ACCELERATION_RULE
#define _MOOMIN_POSITION_ACCELERATION_RULE

#include "model/Rule.hpp"
#include "core/Vec2.hpp"

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
