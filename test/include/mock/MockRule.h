#ifndef _MOOMIN_MOCK_RULE
#define _MOOMIN_MOCK_RULE

#include <gmock/gmock.h>
#include "model/Rule.h"

class MockRule
    : public Rule
{
public:
    MOCK_METHOD2(apply, void(Entity& entity, float timeDelta));
    
};

#endif