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

#include <iostream>
using namespace std;

void Collision::resolveAABBAABB()
{
    AABB & primaryAABB = static_cast<AABB &>(primary);
    AABB & secondaryAABB = static_cast<AABB &>(secondary);

    Vec2 & primaryMin = primaryAABB.getPos();
    Vec2 primaryMax = primaryMin + primaryAABB.getBounding();

    Vec2 & secondaryMin = secondaryAABB.getPos();
    Vec2 secondaryMax = secondaryMin + secondaryAABB.getBounding();

    if (primaryMin.getX() > secondaryMax.getX() ||
        primaryMin.getY() > secondaryMax.getY() ||
        primaryMax.getX() < secondaryMin.getX() ||
        primaryMax.getY() < secondaryMin.getY())
    {
        return;
    } else
    {
        float left = secondaryMin.getX() - primaryMax.getX();
        float right = secondaryMax.getX() - primaryMin.getX();

        float top = secondaryMin.getY() - primaryMax.getY();
        float bottom = secondaryMax.getY() - primaryMin.getY();

        escapeTranslation.setX(abs(left) < right ? left : right);
        escapeTranslation.setY(abs(top) < bottom ? top : bottom);

        if (abs(escapeTranslation.getX()) < abs(escapeTranslation.getY()))
        {
            escapeTranslation.setY(0);
        } else if(abs(escapeTranslation.getX()) > abs(escapeTranslation.getY()))
        {
            escapeTranslation.setX(0);
        }

        depth = escapeTranslation.getMagnitude();

        resultantVelocity.setX(escapeTranslation.getX() / depth);
        resultantVelocity.setY(escapeTranslation.getY() / depth);
    }
}

void Collision::resolveCircleCircle()
{
    Circle & primaryCircle = static_cast<Circle &>(primary);
    Circle & secondaryCircle = static_cast<Circle &>(secondary);


    Vec2 difference = secondaryCircle.getPos() - primaryCircle.getPos();
    float distance = difference.getMagnitude();

    depth = primaryCircle.getRadius() + secondaryCircle.getRadius() - distance;

    if (depth > 0)
    {
        float scale = distance / depth;

        escapeTranslation.setX(-0.5 * (difference.getX() / scale));
        escapeTranslation.setY(-0.5 * (difference.getY() / scale));

        resultantVelocity.setX(-difference.getX() / scale);
        resultantVelocity.setY(-difference.getY() / scale);
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
