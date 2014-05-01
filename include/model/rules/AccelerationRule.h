#ifndef _MOOMIN_ACCELERATION_RULE
#define _MOOMIN_ACCELERATION_RULE

#include "model/Rule.h"
#include "core/Vec2.h"

class AccelerationRule
    : public Rule
{
public:
    AccelerationRule(const Vec2&);
    ~AccelerationRule();

    const Vec2& getAcceleration();
    void apply(Entity&, float delta);
private:
    Vec2 acceleration;
};

#endif