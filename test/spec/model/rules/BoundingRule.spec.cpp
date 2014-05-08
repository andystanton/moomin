#include <bandit/bandit.h>

#include "model/Rule.h"
#include "model/rules/AccelerationRule.h"
#include "model/rules/BoundingRule.h"
#include "model/Circle.h"
#include "core/Vec2.h"

#include "mock/MockEntity.h"

using namespace bandit;

go_bandit([]() 
{
    describe("a Bounding Rule", []()
    {
        BoundingRule area = BoundingRule(0.5f, Vec2(0.f, 0.f), Vec2(640.f, 480.f));

        it("is an instance of a Rule", [&]()
        {
            Rule * areaAsRule = &area;

            MockEntity entity;
            areaAsRule->apply(entity, 100.f);
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

            it("applies its coefficient of friction", [&]()
            {
                entity.setPos(Vec2(50.f, 0.f));
                entity.setVelocity(Vec2(10.f, 0.f));

                area.apply(entity, timeDeltaMilliseconds);

                AssertThat(entity.getVelocity().getX(), Is().EqualTo(9.f));
            });
        });
    });
});
