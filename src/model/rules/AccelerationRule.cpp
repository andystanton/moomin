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

void AccelerationRule::apply(Entity& source, float deltaMilliseconds)
{
    if (source.getVelocity().getY() > 0.1 || source.getPos().getY() > 0.1)
    {
        source.setVelocity(Vec2
            (
                source.getVelocity().getX() + acceleration.getX() * deltaMilliseconds/1000,
                source.getVelocity().getY() + acceleration.getY() * deltaMilliseconds/1000
            )
        );
    }
}