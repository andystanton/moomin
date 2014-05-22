#include "model/rules/BoundingRule.h"

using namespace std;

BoundingRule::BoundingRule(float elasticity, Vec2 lowerLeft, Vec2 upperRight)
    : Rule(Rule::RuleType::bounding)
    , lowerLeft(lowerLeft)
    , upperRight(upperRight)
    , elasticity(elasticity)
{

}

BoundingRule::~BoundingRule()
{

}

void BoundingRule::apply(Entity & entity, float deltaMilliseconds)
{
    switch (entity.getCollisionType())
    {
        case Entity::CollisionType::circle:
            applyToCircle(static_cast<Circle &>(entity), deltaMilliseconds);
            break;
        case Entity::CollisionType::aabb:
            applyToAABB(static_cast<AABB &>(entity), deltaMilliseconds);
            break;
        default:
            break;
    }
}

#include <iostream>
using namespace std;
void BoundingRule::applyToAABB(AABB & aabb, float deltaMilliseconds)
{
    Vec2 & pos = aabb.getPos();
    Vec2 & nextPos = aabb.getNextPos();
    Vec2 & bounding = aabb.getBounding();

    float aabbWidth = bounding.getX();
    float aabbHeight = bounding.getY();

    float aabbLowerLeftX = pos.getX();
    float aabbLowerLeftY = pos.getY();

    float aabbUpperRightX = pos.getX() + aabbWidth;
    float aabbUpperRightY = pos.getY() + aabbHeight;

    if (aabbLowerLeftX >= lowerLeft.getX() && aabbUpperRightX <= upperRight.getX()
            && aabbLowerLeftY > lowerLeft.getY() && aabbUpperRightY <= upperRight.getY())
    {
        return;
    } else
    {
        Vec2 & velocity = aabb.getVelocity();

        float newPosX = aabbLowerLeftX, newPosY = aabbLowerLeftY;
        float newVelocityX = velocity.getX(), newVelocityY = velocity.getY();

        if (aabbLowerLeftX < lowerLeft.getX())
        {
            newPosX = lowerLeft.getX();

            newVelocityX = -1 * (newVelocityX * elasticity);
            newVelocityY = newVelocityY * 0.9;

            if (newVelocityX < 0.5)
            {
                newVelocityX = 0;
            }
        } else if (aabbUpperRightX > upperRight.getX())
        {
            newPosX = upperRight.getX() - aabbWidth;

            newVelocityX = -1 * (newVelocityX * elasticity);
            newVelocityY = newVelocityY * 0.9;

            if (newVelocityX > 0.5)
            {
                newVelocityX = 0;
            }
        }

        if (aabbLowerLeftY < lowerLeft.getY())
        {
            newPosY = lowerLeft.getY();

            newVelocityY = -1 * (newVelocityY * elasticity);
            newVelocityX = newVelocityX * 0.9;

            if (newVelocityY < 0.5)
            {
                newVelocityY = 0;
            }
        } else if (aabbUpperRightY > upperRight.getY())
        {
            newPosY = upperRight.getY() - aabbHeight;

            newVelocityY = -1 * (newVelocityY * elasticity);
            newVelocityX = newVelocityX * 0.9;

            if (newVelocityY > 0.5)
            {
                newVelocityY = 0;
            }
        }

        nextPos.setX(newPosX);
        nextPos.setY(newPosY);

        velocity.setX(newVelocityX);
        velocity.setY(newVelocityY);
    }
}

void BoundingRule::applyToCircle(Circle & c, float deltaMilliseconds)
{
    Vec2 & pos = c.getPos();
    float posX = pos.getX(), posY = pos.getY();

    if (posX >= lowerLeft.getX() + c.getRadius() && posX <= upperRight.getX() - c.getRadius()
            && posY > lowerLeft.getY() + c.getRadius() && posY <= upperRight.getY() - c.getRadius())
    {
        return;
    } else
    {
        Vec2 & velocity = c.getVelocity();
        Vec2 & nextPos = c.getNextPos();

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

        nextPos.setX(newPosX);
        nextPos.setY(newPosY);

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
