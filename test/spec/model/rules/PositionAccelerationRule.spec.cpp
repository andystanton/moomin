#include <bandit/bandit.h>

#include "TestConstants.hpp"
#include "model/Rule.hpp"
#include "model/rules/PositionAccelerationRule.hpp"
#include "model/Circle.hpp"
#include "core/Vec2.hpp"
#include "mock/MockEntity.hpp"

using namespace bandit;

go_bandit([]()
{
    describe("a Position Acceleration Rule", []()
    {
        it("is an instance of a Rule", []()
        {
            Rule * bigCrunch = new PositionAccelerationRule(Vec2(0.f, 0.f), 10.f);

            MockEntity entity;
            bigCrunch->apply(entity, 100.f);
        });

        it("accepts a Vec2 that defines its origin and an acceleration in units/second^2", []()
        {
            PositionAccelerationRule bigCrunch(Vec2(100.f, 50.f), 10.f);

            AssertThat(bigCrunch.getOrigin().getX(), Is().EqualToWithDelta(100.f, FLOAT_EPSILON));
            AssertThat(bigCrunch.getOrigin().getY(), Is().EqualToWithDelta(50.f, FLOAT_EPSILON));
            AssertThat(bigCrunch.getAcceleration(), Is().EqualToWithDelta(10.f, FLOAT_EPSILON));
        });

        it("applies its acceleration to an Entity's velocity towards itself given a time delta in ms", []()
        {
            // set bigCrunch to 10 units/second^2 toward 0,0
            PositionAccelerationRule bigCrunch(Vec2(0.f, 0.f), 10.f);

            Circle entity(Vec2(400.f, 300.f),   10.f);

            // assert that the entity has zero velocity at the start
            AssertThat(entity.getVelocity().getX(), Is().EqualToWithDelta(0.f, FLOAT_EPSILON));
            AssertThat(entity.getVelocity().getY(), Is().EqualToWithDelta(0.f, FLOAT_EPSILON))

            float timeDeltaSeconds = 0.1;

            // after 100ms, assert the expected change in velocity
            bigCrunch.apply(entity, timeDeltaSeconds);

            AssertThat(entity.getVelocity().getX(), Is().EqualToWithDelta(-0.8f, FLOAT_EPSILON));
            AssertThat(entity.getVelocity().getY(), Is().EqualToWithDelta(-0.6f, FLOAT_EPSILON))

            // after another 100ms, assert the expected change in velocity
            bigCrunch.apply(entity, timeDeltaSeconds);

            AssertThat(entity.getVelocity().getX(), Is().EqualToWithDelta(-1.6f, FLOAT_EPSILON));
            AssertThat(entity.getVelocity().getY(), Is().EqualToWithDelta(-1.2f, FLOAT_EPSILON))
        });

        it("can be inverted", []()
        {
            // set bigBang to 10 units/second^2 toward 0,0
            PositionAccelerationRule bigBang(Vec2(0.f, 0.f), 10.f);

            // then invert it
            bigBang.setInverted(true);

            Circle entity(Vec2(400.f, 300.f),   10.f);

            // assert that the entity has zero velocity at the start
            AssertThat(entity.getVelocity().getX(), Is().EqualToWithDelta(0.f, FLOAT_EPSILON));
            AssertThat(entity.getVelocity().getY(), Is().EqualToWithDelta(0.f, FLOAT_EPSILON))

            float timeDeltaSeconds = 0.1;

            // after 100ms, assert the expected change in velocity
            bigBang.apply(entity, timeDeltaSeconds);

            AssertThat(entity.getVelocity().getX(), Is().EqualToWithDelta(0.8f, FLOAT_EPSILON));
            AssertThat(entity.getVelocity().getY(), Is().EqualToWithDelta(0.6f, FLOAT_EPSILON))

            // after another 100ms, assert the expected change in velocity
            bigBang.apply(entity, timeDeltaSeconds);

            AssertThat(entity.getVelocity().getX(), Is().EqualToWithDelta(1.6f, FLOAT_EPSILON));
            AssertThat(entity.getVelocity().getY(), Is().EqualToWithDelta(1.2f, FLOAT_EPSILON))
        });
    });
});
