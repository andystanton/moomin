#include "model/rules/DirectionAccelerationRule.h"

DirectionAccelerationRule::DirectionAccelerationRule(const Vec2& acceleration)
    : acceleration(acceleration)
{
}

DirectionAccelerationRule::~DirectionAccelerationRule()
{
    
}

const Vec2& DirectionAccelerationRule::getAcceleration()
{
    return acceleration;
}

void DirectionAccelerationRule::apply(Entity& entity, float deltaMilliseconds)
{
    Vec2& velocity = entity.getVelocity();
    Vec2& pos = entity.getPos();

    velocity.setX(velocity.getX() + acceleration.getX() * deltaMilliseconds/1000);
    velocity.setY(velocity.getY() + acceleration.getY() * deltaMilliseconds/1000);
}