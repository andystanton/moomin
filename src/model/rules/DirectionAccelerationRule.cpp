#include "model/rules/DirectionAccelerationRule.h"

DirectionAccelerationRule::DirectionAccelerationRule(const Vec2 & acceleration)
    : Rule(Rule::RuleType::direction_acceleration)
    , acceleration(acceleration)
    , directionScale(1)
{

}

DirectionAccelerationRule::~DirectionAccelerationRule()
{

}

Vec2 & DirectionAccelerationRule::getAcceleration()
{
    return acceleration;
}

void DirectionAccelerationRule::apply(Entity & entity, float deltaMilliseconds)
{
    Vec2 & velocity = entity.getVelocity();
    Vec2 & pos = entity.getPos();

    velocity.setX(velocity.getX() + (directionScale * acceleration.getX() * deltaMilliseconds/1000));
    velocity.setY(velocity.getY() + (directionScale * acceleration.getY() * deltaMilliseconds/1000));
}

void DirectionAccelerationRule::setInverted(bool inverted)
{
    directionScale = inverted ? -1 : 1;
}
