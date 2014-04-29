#include "model/rules/AccelerationRule.h"

AccelerationRule::AccelerationRule(const Vec2& acceleration)
    : acceleration(acceleration)
{
}

AccelerationRule::~AccelerationRule()
{
    
}

const Vec2& AccelerationRule::getAcceleration()
{
    return acceleration;
}