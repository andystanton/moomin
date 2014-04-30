#ifndef _MOOMIN_RULE
#define _MOOMIN_RULE

#include "core/Vec2.h"
#include "model/Entity.h"

class Rule
{
public:
    virtual ~Rule() {};
    virtual void apply(Entity&, float delta) = 0;
};

#endif