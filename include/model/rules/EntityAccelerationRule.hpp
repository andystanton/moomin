#ifndef _MOOMIN_ENTITY_ACCELERATION_RULE
#define _MOOMIN_ENTITY_ACCELERATION_RULE

#include "model/Rule.hpp"
#include <set>

using std::set;

class EntityAccelerationRule
    : public Rule
{
public:
    EntityAccelerationRule(const set<Entity *> & entities, float acceleration);
    ~EntityAccelerationRule();

    void apply(Entity&, float delta);
    const set<Entity *> & getEntities();
    void setInverted(bool);
    float getAcceleration();
private:
    const set<Entity *> & entities;
    float acceleration;
    int directionScale;
};

#endif
