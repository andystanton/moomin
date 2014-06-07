#include "model/rules/DirectionAccelerationRule.hpp"

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

void DirectionAccelerationRule::apply(Entity & entity, float deltaSeconds)
{
    entity.getVelocity() += (acceleration * (directionScale * deltaSeconds));
}

void DirectionAccelerationRule::setInverted(bool inverted)
{
    directionScale = inverted ? -1 : 1;
}
