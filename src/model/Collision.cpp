#include "model/Collision.h"

Collision::Collision(Entity& primary, Entity& secondary)
    : primary(primary)
    , secondary(secondary)
    , depth(0)
    , resultantVelocity()
{
    if (&primary != &secondary)
    {
        Circle & primaryCircle = static_cast<Circle &>(primary);
        Circle & secondaryCircle = static_cast<Circle &>(secondary);

        float distance = primaryCircle.getPos().distanceTo(secondaryCircle.getPos());
        depth = primaryCircle.getRadius() + secondaryCircle.getRadius() - distance;

        if (depth > 0)
        {
            float scale = distance / depth;
            unique_ptr<Vec2> difference = secondaryCircle.getPos().subtractFrom(primaryCircle.getPos());

            resultantVelocity.setX(primaryCircle.getVelocity().getX() + difference.get()->getX() / scale);
            resultantVelocity.setY(primaryCircle.getVelocity().getY() + difference.get()->getY() / scale);
        }
    }
}

Collision::~Collision()
{

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
