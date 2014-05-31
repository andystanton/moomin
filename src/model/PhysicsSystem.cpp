#include "model/PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
    : entities()
    , rules()
    , paused(false)
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
    if (!paused)
    {
        // Calculate next position for all entities
        for (auto entity : entities)
        {
            Vec2 & nextPos = entity->getNextPos();
            nextPos.setFrom(entity->getPos());

            for (auto rule : rules)
            {
                if (rule->isEnabled())
                {
                    rule->apply(*entity, deltaInMilliseconds);
                }
            }

            nextPos += entity->getVelocity();
        }

        // Update entity positions
        for (auto entity : entities)
        {
            entity->getPos().setFrom(entity->getNextPos());
        }
    }
}

void PhysicsSystem::clearEntities()
{
    entities.clear();
}

bool PhysicsSystem::isPaused()
{
    return paused;
}

void PhysicsSystem::setPaused(bool paused)
{
    this->paused = paused;
}
