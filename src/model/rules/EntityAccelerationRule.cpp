#include "model/rules/EntityAccelerationRule.h"

EntityAccelerationRule::EntityAccelerationRule(const set<Entity *> & entities)
    : Rule(Rule::RuleType::entity_acceleration)
    , entities(entities)
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
        Vec2 & otherVelocity = other->getVelocity();
        Vec2 & otherPos = other->getPos();

        Vec2 difference = otherPos - pos;
        float distance = difference.getMagnitude();

        int fudgeFactor = 5000000;

        otherVelocity.setX(otherVelocity.getX() - directionScale * (difference.getX() / fudgeFactor) * distance * delta/1000);
        otherVelocity.setY(otherVelocity.getY() - directionScale * (difference.getY() / fudgeFactor) * distance * delta/1000);
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
