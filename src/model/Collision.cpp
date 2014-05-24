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
            default:
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

        // use the nearest edge for the escape translation. If the nearest
        // horizontal and vertical edges are equidistant, the escape translation
        // is the corner.
        if (abs(escapeTranslation.getX()) < abs(escapeTranslation.getY()))
        {
            escapeTranslation.setY(0.f);
        } else if(abs(escapeTranslation.getX()) > abs(escapeTranslation.getY()))
        {
            escapeTranslation.setX(0.f);
        }

        // the collision depth is the magnitude of the full escape translation
        depth = escapeTranslation.getMagnitude();

        // then halve the escape translation because the other AABB should
        // also be doing half the work. an alternative approach might be to
        // only move one, but I would need a way to decide which, and flag
        // other as having already been resolved against this AABB.
        escapeTranslation /= 2.f;

        // placeholder for resultant velocity. currently move the
        // AABB in the direction of the escape translation.
        resultantVelocity = escapeTranslation;
    }
}

void Collision::resolveCircleCircle()
{
    Circle & primaryCircle = static_cast<Circle &>(primary);
    Circle & secondaryCircle = static_cast<Circle &>(secondary);

    Vec2 difference = secondaryCircle.getPos() - primaryCircle.getPos();
    float distance = difference.getMagnitude();

    depth = primaryCircle.getRadius() + secondaryCircle.getRadius() - distance;

    if (depth > 0.f)
    {
        float scale = distance / depth;
        escapeTranslation = 0.5f * difference / -scale;
        resultantVelocity = difference / -scale;
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
