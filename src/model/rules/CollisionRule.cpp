#include "model/rules/CollisionRule.hpp"

CollisionRule::CollisionRule(const set<Entity *>& entities)
    : Rule(Rule::RuleType::collision)
    , entities(entities)
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
            float elasticity = 0.99f;

            Vec2 & primaryNextPos = collision->getPrimary().getNextPos();
            primaryNextPos += collision->getEscapeTranslation();

            Vec2 & primaryVelocity = collision->getPrimary().getVelocity();
            primaryVelocity += collision->getResultantVelocity();
            primaryVelocity *= elasticity;
        }
    }
}
