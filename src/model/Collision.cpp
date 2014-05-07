#include "model/Collision.h"

Collision::Collision(Entity& primary, Entity& secondary)
    : primary(primary)
    , secondary(secondary)
{
    Circle & primaryCircle = static_cast<Circle &>(primary);
    Circle & secondaryCircle = static_cast<Circle &>(secondary);

    depth = primaryCircle.getRadius() + secondaryCircle.getRadius();
    depth = depth - primaryCircle.getPos().distanceTo(secondaryCircle.getPos());
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
