#ifndef _MOOMIN_PHYSICS_SYSTEM
#define _MOOMIN_PHYSICS_SYSTEM

#include <set>

#include "model/Rule.h"
#include "model/Entity.h"

using std::set;

class PhysicsSystem
{
public:
    PhysicsSystem();
    ~PhysicsSystem();

    bool isPaused();
    void setPaused(bool paused);
    void step(float delta);
    void addEntity(Entity *);
    void addRule(Rule *);
    const set<Entity *> & getEntities() const;
    const set<Rule *> & getRules() const;
    void clearEntities();
protected:
    set<Entity *> entities;
    set<Rule *> rules;
    bool paused;
};

#endif
