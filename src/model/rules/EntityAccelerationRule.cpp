#include "model/rules/EntityAccelerationRule.hpp"

EntityAccelerationRule::EntityAccelerationRule(const set<Entity *> & entities, float acceleration)
    : Rule(Rule::RuleType::entity_acceleration)
    , entities(entities)
    , acceleration(acceleration)
    , directionScale(1)
{

}

EntityAccelerationRule::~EntityAccelerationRule()
{

}

void EntityAccelerationRule::apply(Entity & entity, float delta)
{
    Vec2 & pos = entity.getPos();
    for (auto other : entities)
    {
        if (&entity != other)
        {
            Vec2 & otherPos = other->getPos();
            Vec2 & otherVelocity = other->getVelocity();

            Vec2 direction = otherPos - pos;
            direction.normalise();
            direction *= (-directionScale * acceleration * delta/1000);

            otherVelocity += direction;
        }
    }
}

const set<Entity *> & EntityAccelerationRule::getEntities()
{
    return entities;
}

void EntityAccelerationRule::setInverted(bool inverted)
{
    directionScale = inverted ? -1 : 1;
}

float EntityAccelerationRule::getAcceleration()
{
    return acceleration;
}
