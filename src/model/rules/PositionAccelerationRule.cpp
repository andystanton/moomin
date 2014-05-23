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
    Vec2 & pos = entity.getPos();
    Vec2 & velocity = entity.getVelocity();

    Vec2 direction = pos - origin;
    direction.normalise();

    velocity.setX(velocity.getX() + (directionScale * -direction.getX() * acceleration * delta / 1000));
    velocity.setY(velocity.getY() + (directionScale * -direction.getY() * acceleration * delta / 1000));
}

void PositionAccelerationRule::setInverted(bool inverted)
{
    directionScale = inverted ? -1 : 1;
}
