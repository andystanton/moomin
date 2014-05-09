#include "model/rules/GravityRule.h"

GravityRule::GravityRule(const set<Entity *> & entities)
    : entities(entities)
{

}

GravityRule::~GravityRule()
{

}

void GravityRule::apply(Entity & entity, float delta)
{
    Vec2 & pos = entity.getPos();
    for (auto other : entities)
    {
        Vec2 & otherVelocity = other->getVelocity();
        Vec2 & otherPos = other->getPos();
        float distance = pos.distanceTo(otherPos);
        Circle & c = static_cast<Circle &>(entity);
        unique_ptr<Vec2> difference = pos.subtractFrom(otherPos);
        otherVelocity.setX(otherVelocity.getX() - difference.get()->getX() / ((c.getRadius() * 10000000.f) / distance));
        otherVelocity.setY(otherVelocity.getY() - difference.get()->getY() / ((c.getRadius() * 10000000.f) / distance));
    }
}