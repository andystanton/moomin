#include "model/Rule.h"

Rule::Rule(Rule::RuleType ruleType)
    : ruleType(ruleType)
    , enabled(true)
{

}

Rule::RuleType Rule::getType()
{
    return ruleType;
}

bool Rule::isEnabled()
{
    return enabled;
}

void Rule::setEnabled(bool enabled)
{
    this->enabled = enabled;
}
