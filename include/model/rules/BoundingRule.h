#ifndef _MOOMIN_BOUNDING_RULE
#define _MOOMIN_BOUNDING_RULE

#include <cmath>

#include "model/Circle.h"
#include "model/Rule.h"
#include "core/Vec2.h"

class BoundingRule
    : public Rule
{
public:
    BoundingRule(float elasticity, Vec2 lowerLeft, Vec2 upperRight);
    ~BoundingRule();
    
    void apply(Entity&, float delta);
    float getElasticity() const;
    const Vec2& getLowerLeft() const;
    const Vec2& getUpperRight() const;
private:
    Vec2 lowerLeft, upperRight;
    float elasticity;
};

#endif