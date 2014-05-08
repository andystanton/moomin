#include <bandit/bandit.h>

#include <set>

#include "model/Rule.h"
#include "model/Collision.h"
#include "model/rules/CollisionDetectionRule.h"
#include "model/Circle.h"
#include "core/Vec2.h"

#include "mock/MockEntity.h"

using std::set;
using namespace bandit;

go_bandit([]() 
{
    describe("a Collision Detection Rule", []()
    {
        it("is an instance of a Rule", []()
        {
            set<Entity *> entities;
            CollisionDetectionRule circleCollision(entities);

            Rule * circleCollisionAsRule = &circleCollision;

            MockEntity entity;
            circleCollisionAsRule->apply(entity, 100.f);
        });

        it("accepts a set of entities", []()
        {
            set<Entity *> entities;

            Circle c1(10.f, 10.f, 10.f);
            Circle c2(50.f, 10.f, 10.f);

            entities.insert(&c1);
            entities.insert(&c2);

            CollisionDetectionRule circleCollision(entities);
        });

        describe("when two circles collide", []()
        {
            set<Entity *> entities;

            Circle c1(0.f, 0.f, 3.f);
            Circle c2(4.f, 3.f, 3.f);
            Circle c3(100.f, 100.f, 3.f);

            c2.getVelocity().setX(-1.f);

            entities.insert(&c1);
            entities.insert(&c2);
            entities.insert(&c3);

            CollisionDetectionRule circleCollision(entities);

            for (auto entity : entities)
            {
                circleCollision.apply(*entity, 100.f);
            }

            it("gives the Entity an impulse in the opposite direction of the Collision", [&]()
            {
                AssertThat(c1.getVelocity().getX(), Is().EqualTo(-0.8f));
                AssertThat(c1.getVelocity().getY(), Is().EqualTo(-0.6f));
            });
        });
    });
});
