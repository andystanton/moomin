#include "model/Collision.h"

Collision::Collision(Entity& primary, Entity& secondary)
    : primary(primary)
    , secondary(secondary)
    , depth(0)
    , resultantVelocity()
{
    if (&primary != &secondary)
    {
        switch (primary.getCollisionType())
        {
            case Entity::CollisionType::circle:
                if (secondary.getCollisionType() == Entity::CollisionType::circle) resolveCircleCircle();
                break;
            case Entity::CollisionType::aabb:
                if (secondary.getCollisionType() == Entity::CollisionType::aabb) resolveAABBAABB();
                break;
        }
    }
}

Collision::~Collision()
{

}

void Collision::resolveAABBAABB()
{
    AABB & primaryAABB = static_cast<AABB &>(primary);
    AABB & secondaryAABB = static_cast<AABB &>(secondary);

    Vec2 & primaryPosition = primaryAABB.getPos();
    Vec2 & primaryBounding = primaryAABB.getBounding();

    Vec2 & secondaryPosition = secondaryAABB.getPos();
    Vec2 & secondaryBounding = secondaryAABB.getBounding();

    if (primaryPosition.getX() > (secondaryPosition.getX() + secondaryBounding.getX()) ||
        primaryPosition.getY() > (secondaryPosition.getY() + secondaryBounding.getY()) ||
        (primaryPosition.getX() + primaryBounding.getX()) < secondaryPosition.getX() ||
        (primaryPosition.getY() + primaryBounding.getY()) < secondaryPosition.getY())
    {
        return;
    } else
    {
        cout << "collision aabb" << endl;
        unique_ptr<Vec2> difference = secondaryPosition.subtractFrom(primaryPosition);

        depth = difference.get()->getMagnitude();

        //resultantVelocity.setX(difference.get()->getX() / depth);
        //resultantVelocity.setY(difference.get()->getY() / depth);
    }
}

void Collision::resolveCircleCircle()
{
    Circle & primaryCircle = static_cast<Circle &>(primary);
    Circle & secondaryCircle = static_cast<Circle &>(secondary);

    float distance = abs(primaryCircle.getPos().distanceTo(secondaryCircle.getPos()));
    depth = primaryCircle.getRadius() + secondaryCircle.getRadius() - distance;

    if (depth > 0)
    {
        float scale = distance / depth;
        unique_ptr<Vec2> difference = secondaryCircle.getPos().subtractFrom(primaryCircle.getPos());

        resultantVelocity.setX(difference.get()->getX() / scale);
        resultantVelocity.setY(difference.get()->getY() / scale);
    }
}

Entity& Collision::getPrimary()
{
    return primary;
}

Entity& Collision::getSecondary()
{
    return secondary;
}

float Collision::getDepth()
{
    return depth;
}

Vec2 & Collision::getResultantVelocity()
{
    return resultantVelocity;
}
