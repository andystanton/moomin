#ifndef _MOOMIN_BOUNDING_RULE
#define _MOOMIN_BOUNDING_RULE

#include "model/Rule.h"
#include "core/Vec2.h"

class BoundingRule
    : public Rule
{
public:
    BoundingRule(Vec2 lowerLeft, Vec2 upperRight);
    ~BoundingRule();
    
    Vec2 apply(const Vec2&, float delta);
private:
    Vec2 lowerLeft, upperRight;
};

#endif