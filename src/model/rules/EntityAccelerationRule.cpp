#include "model/rules/EntityAccelerationRule.h"

EntityAccelerationRule::EntityAccelerationRule(const set<Entity *> & entities)
    : entities(entities)
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
        float distance = pos.distanceTo(otherPos);
        Circle & c = static_cast<Circle &>(entity);
        Vec2 difference = pos - otherPos;
        otherVelocity.setX(otherVelocity.getX() - difference.getX() / ((c.getRadius() * 10000000.f) / distance));
        otherVelocity.setY(otherVelocity.getY() - difference.getY() / ((c.getRadius() * 10000000.f) / distance));
    }
}

const set<Entity *> & EntityAccelerationRule::getEntities()
{
    return entities;
}
