#ifndef _MOOMIN_MOCK_RULE
#define _MOOMIN_MOCK_RULE

#include <gmock/gmock.h>
#include "model/Rule.hpp"

class MockRule
    : public Rule
{
public:
    MockRule()
        : Rule(Rule::RuleType::mock) {}
    MOCK_METHOD2(apply, void(Entity& entity, float timeDelta));
};

#endif
