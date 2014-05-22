#include "model/rules/PositionAccelerationRule.h"

PositionAccelerationRule::PositionAccelerationRule(const Vec2 & origin, float acceleration)
    : Rule(Rule::RuleType::position_acceleration)
    , origin(origin)
    , acceleration(acceleration)
    , directionScale(1)
{

}

PositionAccelerationRule::~PositionAccelerationRule()
{

}

Vec2 & PositionAccelerationRule::getOrigin()
{
    return origin;
}

void PositionAccelerationRule::apply(Entity & entity, float delta)
{

}

void PositionAccelerationRule::setInverted(bool inverted)
{
    directionScale = inverted ? -1 : 1;
}
