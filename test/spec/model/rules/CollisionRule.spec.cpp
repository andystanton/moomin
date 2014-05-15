#include <bandit/bandit.h>

#include <set>

#include "model/Rule.h"
#include "model/rules/CollisionRule.h"
#include "model/Collision.h"
#include "model/Circle.h"
#include "model/AABB.h"
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
            CollisionRule circleCollision(entities);

            Rule * circleCollisionAsRule = &circleCollision;

            MockEntity entity;
            circleCollisionAsRule->apply(entity, 100.f);
        });

        it("accepts a set of Entities", []()
        {
            set<Entity *> entities;

            Circle c1(10.f, 10.f, 10.f);
            Circle c2(50.f, 10.f, 10.f);

            entities.insert(&c1);
            entities.insert(&c2);

            CollisionRule circleCollision(entities);
        });

        describe("when two Circles collide", []()
        {
            float tolerance = 0.001;
            float circleElasticity = 0.65;

            set<Entity *> entities;

            Circle c1(0.f, 0.f, 3.f);
            Circle c2(4.f, 3.f, 3.f);
            Circle c3(100.f, 100.f, 3.f);

            c2.getVelocity().setX(-1.f);

            entities.insert(&c1);
            entities.insert(&c2);
            entities.insert(&c3);

            CollisionRule circleCollision(entities);

            for (auto entity : entities)
            {
                circleCollision.apply(*entity, 100.f);
            }

            it("repositions the Entities so that they are no longer colliding", [&]()
            {
                AssertThat(c1.getNextPos().getX(), Is().EqualToWithDelta(-0.4, tolerance));
                AssertThat(c1.getNextPos().getY(), Is().EqualToWithDelta(-0.3, tolerance));

                AssertThat(c2.getNextPos().getX(), Is().EqualToWithDelta(4.4, tolerance));
                AssertThat(c2.getNextPos().getY(), Is().EqualToWithDelta(3.3, tolerance));
            });

            it("gives the Circle an impulse in the opposite direction of the Collision", [&]()
            {
                AssertThat(c1.getVelocity().getX(), Is().EqualToWithDelta(-0.8 * circleElasticity, tolerance));
                AssertThat(c1.getVelocity().getY(), Is().EqualToWithDelta(-0.6 * circleElasticity, tolerance));

                AssertThat(c2.getVelocity().getX(), Is().EqualToWithDelta((-1 + 0.8) * circleElasticity, tolerance));
                AssertThat(c2.getVelocity().getY(), Is().EqualToWithDelta(0.6 * circleElasticity, tolerance));
            });
        });

        describe("when two AABBs collide", []()
        {
            set<Entity *> entities;

            AABB aabb1(   0.f,   0.f, 40.f, 30.f);
            AABB aabb2( -36.f, -27.f, 40.f, 30.f);
            AABB aabb3( 100.f, 100.f, 20.f, 10.f);

            it("gives the AABB an impulse in the opposite direction of the Collision", [&]()
            {
                float tolerance = 0.001;
                float aabbElasticity = 0.65;
                // AssertThat(aabb1.getVelocity().getX(), Is().EqualToWithDelta(-0.8 * aabbElasticity, tolerance));
                // AssertThat(aabb1.getVelocity().getY(), Is().EqualToWithDelta(-0.6 * aabbElasticity, tolerance));

                // AssertThat(aabb2.getVelocity().getX(), Is().EqualToWithDelta((-1 + 0.8) * aabbElasticity, tolerance));
                // AssertThat(aabb2.getVelocity().getY(), Is().EqualToWithDelta(0.6 * aabbElasticity, tolerance));
            });
        });
    });
});
