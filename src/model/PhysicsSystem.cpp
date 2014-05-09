#include "model/PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
    : entities()
{

}

PhysicsSystem::~PhysicsSystem()
{
    entities.clear();
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
    for (auto entity : entities)
    {
        for (auto rule : rules)
        {
            rule->apply(*entity, deltaInMilliseconds);
        }
        Vec2 & pos = entity->getPos();
        Vec2 & velocity = entity->getVelocity();
        pos.setX(pos.getX() + velocity.getX());
        pos.setY(pos.getY() + velocity.getY());
    }
}