#ifndef _MOOMIN_COLLISION_RULE
#define _MOOMIN_COLLISION_RULE

#include "model/Rule.h"

class CollisionRule
    : public Rule
{
public:
    CollisionRule();
    ~CollisionRule();

    void apply(Entity&, float delta);
    
};

#endif