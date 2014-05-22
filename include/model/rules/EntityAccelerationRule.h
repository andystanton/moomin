#ifndef _MOOMIN_GRAVITY_RULE
#define _MOOMIN_GRAVITY_RULE

#include "model/Rule.h"
#include "model/Circle.h"
#include <set>

using std::set;

class EntityAccelerationRule
    : public Rule
{
public:
    EntityAccelerationRule(const set<Entity *> & entities);
    ~EntityAccelerationRule();

    void apply(Entity&, float delta);
    const set<Entity *> & getEntities();
    void setInverted(bool);
private:
    const set<Entity *> & entities;
    int directionScale;
};

#endif
