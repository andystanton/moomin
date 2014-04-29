#include "model/PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
    : entities()
{

}

PhysicsSystem::~PhysicsSystem()
{

}

const set<Entity *> & PhysicsSystem::getEntities() const
{
    return entities;
}

void PhysicsSystem::addEntity(Entity * entity)
{
    entities.insert(entity);
}

const set<Rule *> & PhysicsSystem::getRules() const
{
    return rules;
}

void PhysicsSystem::addRule(Rule * rule)
{
    rules.insert(rule);
}