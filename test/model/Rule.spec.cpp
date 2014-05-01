#include <bandit/bandit.h>

#include "model/Rule.h"
#include "model/rules/AccelerationRule.h"
#include "model/rules/BoundingRule.h"

#include "model/Circle.h"

#include "core/Vec2.h"

using namespace bandit;

go_bandit([]() 
{
    describe("a Rule", []() 
    {
        it("affects an Entity with a time delta in ms", []()
        {
            Rule * gravity = new AccelerationRule(Vec2(0.f, -10.f));
            Entity * entity = new Circle(100.f, 100.f, 10.f);

            gravity->apply(*entity, 100.f);
        });

        describe("an Acceleration Rule", []()
        {
            it("is an instance of a Rule", []()
            {
                Rule * gravity = new AccelerationRule(Vec2(0.f, -10.f));
            });

            it("accepts a Vec2 that defines its acceleration in units/second^2", []() 
            {
                AccelerationRule gravity(Vec2(0.f, -10.f));

                AssertThat(gravity.getAcceleration().getX(), Is().EqualTo(0.f));
                AssertThat(gravity.getAcceleration().getY(), Is().EqualTo(-10.f));
            });

            it("applies its acceleration to an Entity's velocity given a time delta in ms", []() 
            {
                // set gravity to (0, -10) units/second^2
                AccelerationRule gravity(Vec2(0.f, -10.f));

                Circle entity(100.f, 100.f, 10.f);

                // assert that the entity has zero velocity at the start
                AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
                AssertThat(entity.getVelocity().getY(), Is().EqualTo(0.f))

                float timeDeltaMilliseconds = 100;

                // after 100ms, assert the expected change in velocity
                gravity.apply(entity, timeDeltaMilliseconds);

                AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
                AssertThat(entity.getVelocity().getY(), Is().EqualTo(-1.f))

                // after another 100ms, assert the expected change in velocity
                gravity.apply(entity, timeDeltaMilliseconds);
                
                AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
                AssertThat(entity.getVelocity().getY(), Is().EqualTo(-2.f))

                float longerTimeDeltaMilliseconds = 500;

                // this time increase delta to 500 ms
                gravity.apply(entity, longerTimeDeltaMilliseconds);

                AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
                AssertThat(entity.getVelocity().getY(), Is().EqualTo(-7.f))
            });
        });

        describe("a Bounding Rule", []()
        {
            BoundingRule area = BoundingRule(0.5f, Vec2(0.f, 0.f), Vec2(640.f, 480.f));

            it("is an instance of a Rule", [&]()
            {
                Rule * rule = &area;
            });

            it("accepts an elasticity coefficient", [&]() {
                AssertThat(area.getElasticity(), Is().EqualTo(0.5f));
            });

            it("accepts two Vec2 for its lower left and upper right bounds", [&]()
            {
                AssertThat(area.getLowerLeft().getX(), Is().EqualTo(0.f));
                AssertThat(area.getLowerLeft().getY(), Is().EqualTo(0.f));

                AssertThat(area.getUpperRight().getX(), Is().EqualTo(640.f));
                AssertThat(area.getUpperRight().getY(), Is().EqualTo(480.f));
            });

            describe("when an Entity crosses the rule's bounds", [&]()
            {
                Circle entity(100.f, 100.f, 10.f);
                float timeDeltaMilliseconds = 100;

                it("inverts the components of an Entity's velocity", [&]()
                {
                    entity.setPos(Vec2(-10.f, 100.f));
                    entity.setVelocity(Vec2(-100.f, 0.f));

                    area.apply(entity, timeDeltaMilliseconds);

                    AssertThat(entity.getVelocity().getX(), Is().GreaterThan(0.f));
                    AssertThat(entity.getVelocity().getY(), Is().EqualTo(0.f));

                    entity.setPos(Vec2(650.f, 500.f));
                    entity.setVelocity(Vec2(10.f, 15.f));

                    area.apply(entity, timeDeltaMilliseconds);

                    AssertThat(entity.getVelocity().getX(), Is().LessThan(0.f));
                    AssertThat(entity.getVelocity().getY(), Is().LessThan(0.f));

                });

                it("moves the Entity to the nearest bound", [&]()
                {
                    // first test - move to the nearest bound
                    entity.setPos(Vec2(-10.f, 100.f));
                    entity.setVelocity(Vec2(-100.f, 0.f));

                    area.apply(entity, timeDeltaMilliseconds);

                    AssertThat(entity.getPos().getX(), Is().EqualTo(0.f));
                    AssertThat(entity.getPos().getY(), Is().EqualTo(100.f));

                    // second test - move to the nearest corner
                    entity.setPos(Vec2(-10.f, -12.f));
                    entity.setVelocity(Vec2(-3.f, -4.f));

                    area.apply(entity, timeDeltaMilliseconds);

                    AssertThat(entity.getPos().getX(), Is().EqualTo(0.f));
                    AssertThat(entity.getPos().getY(), Is().EqualTo(0.f));
                });

                it("applies its coefficient of elasticity", [&]()
                {
                    entity.setPos(Vec2(-10.f, 100.f));
                    entity.setVelocity(Vec2(-100.f, 0.f));

                    area.apply(entity, timeDeltaMilliseconds);

                    AssertThat(entity.getVelocity().getX(), Is().EqualTo(50.f));
                });
            });
        });
    });
});
