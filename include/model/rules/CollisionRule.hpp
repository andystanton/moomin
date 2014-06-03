#ifndef _MOOMIN_COLLISION_RULE
#define _MOOMIN_COLLISION_RULE

#include <set>
#include "model/Collision.hpp"
#include "model/Rule.hpp"

using std::set;

class CollisionRule
    : public Rule
{
public:
    CollisionRule(const set<Entity *> &);
    ~CollisionRule();

    void apply(Entity&, float delta);
private:
    const set<Entity *> & entities;
};

#endif
