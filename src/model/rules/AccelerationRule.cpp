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

void AccelerationRule::apply(Entity& entity, float deltaMilliseconds)
{
    Vec2& velocity = entity.getVelocity();
    Vec2& pos = entity.getPos();
    if (velocity.getY() > 0.1 || pos.getY() > 0.1)
    {
        velocity.setX(velocity.getX() + acceleration.getX() * deltaMilliseconds/1000);
        velocity.setY(velocity.getY() + acceleration.getY() * deltaMilliseconds/1000);
        pos.setX(pos.getX() + velocity.getX());
        pos.setY(pos.getY() + velocity.getY());
    }
}