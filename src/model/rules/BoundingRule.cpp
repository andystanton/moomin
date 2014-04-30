#include "model/rules/BoundingRule.h"

BoundingRule::BoundingRule(Vec2 lowerLeft, Vec2 upperRight)
    : lowerLeft(lowerLeft)
    , upperRight(upperRight)
{

}

BoundingRule::~BoundingRule()
{

}

Vec2 BoundingRule::apply(const Vec2& original, float delta)
{
    return Vec2(original); // pass through for now
}