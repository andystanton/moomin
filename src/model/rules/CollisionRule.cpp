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
            Vec2 & primaryVelocity = entity.getVelocity();
            float elasticity = 0.65f;

            cout << collision->getResultantVelocity().getX() << ", " << collision->getResultantVelocity().getY() << endl;

            primaryVelocity.setX((primaryVelocity.getX() + collision->getResultantVelocity().getX()) * elasticity);
            primaryVelocity.setY((primaryVelocity.getY() + collision->getResultantVelocity().getY()) * elasticity);
        }
    }
}

