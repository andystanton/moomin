#include "model/rules/CollisionDetectionRule.h"

CollisionDetectionRule::CollisionDetectionRule(const set<Entity *>& entities)
    : entities(entities)
{

}

CollisionDetectionRule::~CollisionDetectionRule()
{

}

void CollisionDetectionRule::apply(Entity & entity, float delta)
{
    for (auto other : entities)
    {
        unique_ptr<Collision> collision = unique_ptr<Collision>(new Collision(entity, *other));
        if (collision->getDepth() > 0)
        {
            Vec2 & primaryVelocity = collision->getPrimary().getVelocity();
            primaryVelocity.setX((primaryVelocity.getX() + collision->getResultantVelocity().getX()) * 0.5);
            primaryVelocity.setY((primaryVelocity.getY() + collision->getResultantVelocity().getY()) * 0.5);
        }
    }
}

