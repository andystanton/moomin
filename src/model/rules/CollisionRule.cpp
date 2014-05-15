#include "model/rules/CollisionRule.h"

CollisionRule::CollisionRule(const set<Entity *>& entities)
    : entities(entities)
{

}

CollisionRule::~CollisionRule()
{

}

void CollisionRule::apply(Entity & entity, float delta)
{
    for (auto other : entities)
    {
        unique_ptr<Collision> collision = unique_ptr<Collision>(new Collision(entity, *other));
        if (collision->getDepth() > 0)
        {
            Vec2 & primaryPos = collision->getPrimary().getPos();
            Vec2 & primaryNextPos = collision->getPrimary().getNextPos();
            Vec2 & primaryVelocity = collision->getPrimary().getVelocity();

            Vec2 & escapeTranslation = collision->getEscapeTranslation();

            float elasticity = 0.65f;

            primaryNextPos.setX(primaryNextPos.getX() + escapeTranslation.getX());
            primaryNextPos.setY(primaryNextPos.getY() + escapeTranslation.getY());

            primaryVelocity.setX((primaryVelocity.getX() + collision->getResultantVelocity().getX()) * elasticity);
            primaryVelocity.setY((primaryVelocity.getY() + collision->getResultantVelocity().getY()) * elasticity);
        }
    }
}

