#include "model/rules/BoundingRule.h"

#include <iostream>
#include <cmath>
using namespace std;

BoundingRule::BoundingRule(float elasticity, Vec2 lowerLeft, Vec2 upperRight)
    : elasticity(elasticity)
    , lowerLeft(lowerLeft)
    , upperRight(upperRight)
{

}

BoundingRule::~BoundingRule()
{

}

void BoundingRule::apply(Entity& source, float deltaMilliseconds)
{
    const Vec2& pos = source.getPos();
    float posX = pos.getX(), posY = pos.getY();

    if (posX >= lowerLeft.getX() && posX <= upperRight.getX()
            && posY >= lowerLeft.getX() && posY <= upperRight.getY())
    {
        cout << "no collision" << endl;
        return;
    } else
    {
        cout << "collision" << endl;
        const Vec2& velocity = source.getVelocity();
        const Vec2& pos = source.getPos();

        cout << "source pos: " << pos.getX() << ", " << pos.getY() << endl;
        cout << "source velocity: " << velocity.getX() << ", " << velocity.getY() << endl;

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
        }

        cout << "new pos: " << newPosX << ", " << newPosY << endl;
        cout << "new velocity: " << newVelocityX << ", " << newVelocityY << endl;

        source.setPos(Vec2(newPosX, newPosY));
        source.setVelocity(Vec2(newVelocityX, newVelocityY));
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