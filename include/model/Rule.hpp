#ifndef _MOOMIN_RULE
#define _MOOMIN_RULE

#include "core/Vec2.hpp"
#include "model/Entity.hpp"

class Rule
{
public:
    enum class RuleType
    {
        mock,
        bounding,
        collision,
        direction_acceleration,
        entity_acceleration,
        position_acceleration
    };

    RuleType getType();
    bool isEnabled();
    void setEnabled(bool);
    virtual ~Rule() {};
    virtual void apply(Entity&, float delta) = 0;
protected:
    Rule(RuleType);
private:
    RuleType ruleType;
    bool enabled;
};

#endif
