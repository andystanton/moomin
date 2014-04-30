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

Vec2 AccelerationRule::apply(const Vec2& source, float deltaMilliseconds)
{
    return Vec2(
        source.getX() + acceleration.getX() * deltaMilliseconds/1000,
        source.getY() + acceleration.getY() * deltaMilliseconds/1000
    );
}