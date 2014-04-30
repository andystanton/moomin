#ifndef _MOOMIN_RULE
#define _MOOMIN_RULE

#include "core/Vec2.h"

class Rule
{
public:
    virtual ~Rule() {};
    virtual Vec2 apply(const Vec2&, float delta) = 0;
};

#endif