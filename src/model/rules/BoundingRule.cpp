#include "model/rules/BoundingRule.h"

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

void BoundingRule::apply(Entity & entity, float deltaMilliseconds)
{
    Vec2& pos = entity.getPos();
    float posX = pos.getX(), posY = pos.getY();

    Circle & c = static_cast<Circle &>(entity);

    if (posX >= lowerLeft.getX() + c.getRadius() && posX <= upperRight.getX() - c.getRadius()
            && posY > lowerLeft.getY() + c.getRadius() && posY <= upperRight.getY() - c.getRadius())
    {
        return;
    } else
    {
        Vec2& velocity = entity.getVelocity();

        float newPosX = posX, newPosY = posY;
        float newVelocityX = velocity.getX(), newVelocityY = velocity.getY();

        if (posX < lowerLeft.getX() + c.getRadius()) 
        {
            newPosX = lowerLeft.getX() + c.getRadius();

            newVelocityX = -1 * (newVelocityX * elasticity);
            newVelocityY = newVelocityY * 0.9;

            if (newVelocityX < 0.5)
            {
                newVelocityX = 0;
            }
        } else if (posX > upperRight.getX() - c.getRadius())
        {
            newPosX = upperRight.getX() - c.getRadius();

            newVelocityX = -1 * (newVelocityX * elasticity);
            newVelocityY = newVelocityY * 0.9;

            if (newVelocityX > 0.5)
            {
                newVelocityX = 0;
            }
        }

        if (posY < lowerLeft.getY() + c.getRadius())
        {
            newPosY = lowerLeft.getY() + c.getRadius();

            newVelocityX = newVelocityX * 0.9;
            newVelocityY = -1 * (newVelocityY * elasticity);

            if (newVelocityY < 0.5)
            {
                newVelocityY = 0;
            }
        } else if (posY > upperRight.getY() - c.getRadius())
        {
            newPosY = upperRight.getY() - c.getRadius();

            newVelocityX = newVelocityX * 0.9;
            newVelocityY = -1 * (newVelocityY * elasticity);

            if (newVelocityY > 0.5)
            {
                newVelocityY = 0;
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
