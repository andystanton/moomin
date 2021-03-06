#include <bandit/bandit.h>

#include "TestConstants.hpp"
#include "model/Rule.hpp"
#include "model/rules/DirectionAccelerationRule.hpp"
#include "model/Circle.hpp"
#include "core/Vec2.hpp"

#include "mock/MockEntity.hpp"

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

            float timeDeltaSeconds = 0.1;

            // after 100ms, assert the expected change in velocity
            gravity.apply(entity, timeDeltaSeconds);

            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2( 0.f, -1.f)));

            // after another 100ms, assert the expected change in velocity
            gravity.apply(entity, timeDeltaSeconds);

            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2( 0.f, -2.f)));

            float longerTimeDeltaSeconds = 0.5;

            // this time increase delta to 500 ms
            gravity.apply(entity, longerTimeDeltaSeconds);

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

            float timeDeltaSeconds = 0.1;

            // after 100ms, assert the expected change in velocity
            gravity.apply(entity, timeDeltaSeconds);

            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2(0.f, 1.f)));

            // after another 100ms, assert the expected change in velocity
            gravity.apply(entity, timeDeltaSeconds);

            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2(0.f, 2.f)));

            float longerTimeDeltaSeconds = 0.5;

            // this time increase delta to 500 ms
            gravity.apply(entity, longerTimeDeltaSeconds);

            AssertThat(entity.getVelocity(), Is().EqualTo(Vec2(0.f, 7.f)));
        });
    });
});
