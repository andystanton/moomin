#ifndef _MOOMIN_GRAVITY_RULE
#define _MOOMIN_GRAVITY_RULE

#include "model/Rule.h"
#include "model/Circle.h"
#include <set>

using std::set;

class GravityRule
    : public Rule
{
public:
    GravityRule(const set<Entity *> & entities);
    ~GravityRule();

    void apply(Entity&, float delta);
private:
    const set<Entity *> & entities;
};

#endif