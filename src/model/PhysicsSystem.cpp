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

void PhysicsSystem::step(float deltaInMilliseconds)
{
    for (auto rule : rules)
    {
        for (auto entity : entities)
        {
            rule->apply(*entity, deltaInMilliseconds);
        }
    }
}