#include <bandit/bandit.h>

#include "TestConstants.h"
#include "model/Rule.h"
#include "model/rules/DirectionAccelerationRule.h"
#include "model/Circle.h"
#include "core/Vec2.h"

#include "mock/MockEntity.h"

using namespace bandit;

go_bandit([]()
{
    describe("a Direction Acceleration Rule", []()
    {
        it("is an instance of a Rule", []()
        {
            Rule * gravity = new DirectionAccelerationRule(Vec2(0.f, -10.f));

            MockEntity entity;
            gravity->apply(entity, 100.f);
        });

        it("accepts a Vec2 that defines its acceleration in units/second^2", []()
        {
            DirectionAccelerationRule gravity(Vec2(0.f, -10.f));

            AssertThat(gravity.getAcceleration(), Is().EqualTo(Vec2(  0.f, -10.f)));
        });

        it("applies its acceleration to an Entity's velocity given a time delta in ms", []()
        {
            // set gravity to (0, -10) units/second^2
            DirectionAccelerationRule gravity(Vec2(0.f, -10.f));

            Circle entity(Vec2(100.f, 100.f),   10.f);

            // assert that the entity has zero velocity at the start
            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2(0.f, 0.f)));

            float timeDeltaMilliseconds = 100;

            // after 100ms, assert the expected change in velocity
            gravity.apply(entity, timeDeltaMilliseconds);

            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2( 0.f, -1.f)));

            // after another 100ms, assert the expected change in velocity
            gravity.apply(entity, timeDeltaMilliseconds);

            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2( 0.f, -2.f)));

            float longerTimeDeltaMilliseconds = 500;

            // this time increase delta to 500 ms
            gravity.apply(entity, longerTimeDeltaMilliseconds);

            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2( 0.f, -7.f)));
        });

        it("can be inverted", []()
        {
            // set gravity to (0, -10) units/second^2
            DirectionAccelerationRule gravity(Vec2(0.f, -10.f));
            gravity.setInverted(true);

            Circle entity(Vec2(100.f, 100.f),   10.f);

            // assert that the entity has zero velocity at the start
            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2(0.f, 0.f)));

            float timeDeltaMilliseconds = 100;

            // after 100ms, assert the expected change in velocity
            gravity.apply(entity, timeDeltaMilliseconds);

            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2(0.f, 1.f)));

            // after another 100ms, assert the expected change in velocity
            gravity.apply(entity, timeDeltaMilliseconds);

            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2(0.f, 2.f)));

            float longerTimeDeltaMilliseconds = 500;

            // this time increase delta to 500 ms
            gravity.apply(entity, longerTimeDeltaMilliseconds);

            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2(0.f, 7.f)));
        });
    });
});
