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