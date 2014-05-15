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
        Vec2 & pos = entity->getPos();
        Vec2 & nextPos = entity->getNextPos();

        nextPos.setX(pos.getX());
        nextPos.setY(pos.getY());

        for (auto rule : rules)
        {
            rule->apply(*entity, deltaInMilliseconds);
        }

        Vec2 & velocity = entity->getVelocity();

        nextPos.setX(nextPos.getX() + velocity.getX());
        nextPos.setY(nextPos.getY() + velocity.getY());
    }
    for (auto entity : entities)
    {
        Vec2 & pos = entity->getPos();
        Vec2 & nextPos = entity->getNextPos();

        pos.setX(nextPos.getX());
        pos.setY(nextPos.getY());
    }
}