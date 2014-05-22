#ifndef _MOOMIN_DIRECTION_ACCELERATION_RULE
#define _MOOMIN_DIRECTION_ACCELERATION_RULE

#include "model/Rule.h"
#include "core/Vec2.h"

class DirectionAccelerationRule
    : public Rule
{
public:
    DirectionAccelerationRule(const Vec2 &);
    ~DirectionAccelerationRule();

    Vec2 & getAcceleration();
    void apply(Entity &, float delta);
    void setInverted(bool);
private:
    Vec2 acceleration;
    int directionScale;
};

#endif
