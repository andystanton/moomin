#include "model/Collision.h"

Collision::Collision(Entity& primary, Entity& secondary)
    : primary(primary)
    , secondary(secondary)
    , depth(0)
    , resultantVelocity()
    , escapeTranslation()
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

    Vec2 & primaryMin = primaryAABB.getPos();
    unique_ptr<Vec2> primaryMax = primaryMin.addTo(primaryAABB.getBounding());

    Vec2 & secondaryMin = secondaryAABB.getPos();
    unique_ptr<Vec2> secondaryMax = secondaryMin.addTo(secondaryAABB.getBounding());

    if (primaryMin.getX() > secondaryMax.get()->getX() ||
        primaryMin.getY() > secondaryMax.get()->getY() ||
        primaryMax.get()->getX() < secondaryMin.getX() ||
        primaryMax.get()->getY() < secondaryMin.getY())
    {
        return;
    } else
    {
        float left = secondaryMin.getX() - primaryMax.get()->getX();
        float right = secondaryMax.get()->getX() - primaryMin.getX();

        float top = secondaryMin.getY() - primaryMax.get()->getY();
        float bottom = secondaryMax.get()->getY() - primaryMin.getY();

        escapeTranslation.setX(abs(left) < right ? left : right);
        escapeTranslation.setY(abs(top) < bottom ? top : bottom);

        unique_ptr<Vec2> difference = secondaryMin.subtractFrom(primaryMin);

        depth = escapeTranslation.getMagnitude();

        if (escapeTranslation.getX() < escapeTranslation.getY())
        {
            escapeTranslation.setY(0);
        } else {
            escapeTranslation.setX(0);
        }

        resultantVelocity.setX(difference.get()->getX() / depth);
        resultantVelocity.setY(difference.get()->getY() / depth);
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

Vec2 & Collision::getEscapeTranslation()
{
    return escapeTranslation;
}
