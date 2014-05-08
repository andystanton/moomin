#include "model/rules/BoundingRule.h"

#include <iostream>
#include <cmath>

using namespace std;

BoundingRule::BoundingRule(float elasticity, Vec2 lowerLeft, Vec2 upperRight)
    : lowerLeft(lowerLeft)
    , upperRight(upperRight)
    , elasticity(elasticity)
{

}

BoundingRule::~BoundingRule()
{

}

void BoundingRule::apply(Entity& source, float deltaMilliseconds)
{
    Vec2& pos = source.getPos();
    float posX = pos.getX(), posY = pos.getY();

    if (posX >= lowerLeft.getX() && posX <= upperRight.getX()
            && posY > lowerLeft.getY() && posY <= upperRight.getY())
    {
        return;
    } else
    {
        Vec2& velocity = source.getVelocity();

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
            newVelocityY = abs(newVelocityY * elasticity);
            if (newVelocityY < 0.5)
            {
                newVelocityY = 0;
            }
        } else if (posY > upperRight.getY())
        {
            newPosY = upperRight.getY();
            newVelocityY = -1 * abs(newVelocityY * elasticity);
        } else if(posY == lowerLeft.getY())
        {
            if (newVelocityY == 0)
            {
                newVelocityX = newVelocityX * 0.95;
            }
        }

        pos.setX(newPosX);
        pos.setY(newPosY);

        velocity.setX(newVelocityX);
        velocity.setY(newVelocityY);

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
