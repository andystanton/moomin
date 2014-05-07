#include "model/rules/CollisionRule.h"

CollisionRule::CollisionRule(const set<Entity *>& entities)
    : collisions()
    , entities(entities)
{

}

CollisionRule::~CollisionRule()
{
    collisions.clear();
}

void CollisionRule::apply(Entity & entity, float delta)
{
    for (auto other : entities)
    {
        Collision * collision = new Collision(entity, *other);
        if (collision->getDepth() > 0)
        {
            collisions.insert(collision);
        } else
        {
            delete collision;
        }
    }
}

set<Collision *>& CollisionRule::getCollisions()
{
    return collisions;
}