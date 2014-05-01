#include "model/rules/BoundingRule.h"

BoundingRule::BoundingRule(float elasticity, Vec2 lowerLeft, Vec2 upperRight)
    : elasticity(elasticity)
    , lowerLeft(lowerLeft)
    , upperRight(upperRight)
{

}

BoundingRule::~BoundingRule()
{

}

void BoundingRule::apply(Entity& original, float delta)
{
    // pass through for now
    const Vec2& pos = original.getPos();
    float posX = pos.getX(), posY = pos.getY();

    if (posX >= lowerLeft.getX() && posX <= upperRight.getX()
            && posY >= lowerLeft.getX() && posY <= upperRight.getY())
    {
        return;
    } else
    {
        const Vec2& velocity = original.getVelocity();

        float newPosX = posX, newPosY = posY;
        float newVelocityX = velocity.getX(), newVelocityY = velocity.getY();

        if (posX < lowerLeft.getX()) 
        {
            newPosX = lowerLeft.getX();
            newVelocityX = -newVelocityX * elasticity;
        } else if (posX > upperRight.getX())
        {
            newPosX = upperRight.getX();
            newVelocityX = -newVelocityX * elasticity;
        }

        if (posY < lowerLeft.getY())
        {
            newPosY = lowerLeft.getY();
            newVelocityY = -newVelocityY * elasticity;
        } else if (posY > upperRight.getY())
        {
            newPosY = upperRight.getY();
            newVelocityY = -newVelocityY * elasticity;
        }

        original.setPos(Vec2(newPosX, newPosY));
        original.setVelocity(Vec2(newVelocityX, newVelocityY));
    }
}

float BoundingRule::getElasticity() const
{
    return elasticity;
}

const Vec2& BoundingRule::getLowerLeft() const
{
    return lowerLeft;
}

const Vec2& BoundingRule::getUpperRight() const
{
    return upperRight;
}