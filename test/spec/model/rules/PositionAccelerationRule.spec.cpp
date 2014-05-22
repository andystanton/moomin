#include <bandit/bandit.h>

#include "model/Rule.h"
#include "model/rules/PositionAccelerationRule.h"
#include "model/Circle.h"
#include "core/Vec2.h"

#include "mock/MockEntity.h"

using namespace bandit;

go_bandit([]()
{
    describe("a Position Acceleration Rule", []()
    {
        it("is an instance of a Rule", []()
        {
            Rule * singularity = new PositionAccelerationRule(Vec2(0.f, 0.f), 10.f);

            MockEntity entity;
            singularity->apply(entity, 100.f);
        });

        it("accepts a Vec2 that defines its origin and an acceleration in units/second^2", []()
        {
            PositionAccelerationRule singularity(Vec2(100.f, 50.f), 10.f);

            AssertThat(singularity.getOrigin().getX(), Is().EqualTo(100.f));
            AssertThat(singularity.getOrigin().getY(), Is().EqualTo(50.f));
        });

        // it("applies its acceleration to an Entity's velocity towards itself given a time delta in ms", []()
        // {
        //     // set gravity to (0, -10) units/second^2
        //     PositionAccelerationRule singularity(Vec2(0.f, 0.f), 10.f);
        //
        //     Circle entity(100.f, 100.f, 10.f);
        //
        //     // assert that the entity has zero velocity at the start
        //     AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
        //     AssertThat(entity.getVelocity().getY(), Is().EqualTo(0.f))
        //
        //     float timeDeltaMilliseconds = 100;
        //
        //     // after 100ms, assert the expected change in velocity
        //     singularity.apply(entity, timeDeltaMilliseconds);
        //
        //     AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
        //     AssertThat(entity.getVelocity().getY(), Is().EqualTo(-1.f))
        //
        //     // after another 100ms, assert the expected change in velocity
        //     singularity.apply(entity, timeDeltaMilliseconds);
        //
        //     AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
        //     AssertThat(entity.getVelocity().getY(), Is().EqualTo(-2.f))
        //
        //     float longerTimeDeltaMilliseconds = 500;
        //
        //     // this time increase delta to 500 ms
        //     singularity.apply(entity, longerTimeDeltaMilliseconds);
        //
        //     AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
        //     AssertThat(entity.getVelocity().getY(), Is().EqualTo(-7.f))
        // });
        //
        // it("can be inverted", []()
        // {
        //     // set gravity to (0, -10) units/second^2
        //     DirectionAccelerationRule gravity(Vec2(0.f, -10.f));
        //     gravity.setInverted(true);
        //
        //     Circle entity(100.f, 100.f, 10.f);
        //
        //     // assert that the entity has zero velocity at the start
        //     AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
        //     AssertThat(entity.getVelocity().getY(), Is().EqualTo(0.f))
        //
        //     float timeDeltaMilliseconds = 100;
        //
        //     // after 100ms, assert the expected change in velocity
        //     gravity.apply(entity, timeDeltaMilliseconds);
        //
        //     AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
        //     AssertThat(entity.getVelocity().getY(), Is().EqualTo(1.f))
        //
        //     // after another 100ms, assert the expected change in velocity
        //     gravity.apply(entity, timeDeltaMilliseconds);
        //
        //     AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
        //     AssertThat(entity.getVelocity().getY(), Is().EqualTo(2.f))
        //
        //     float longerTimeDeltaMilliseconds = 500;
        //
        //     // this time increase delta to 500 ms
        //     gravity.apply(entity, longerTimeDeltaMilliseconds);
        //
        //     AssertThat(entity.getVelocity().getX(), Is().EqualTo(0.f));
        //     AssertThat(entity.getVelocity().getY(), Is().EqualTo(7.f))
        // });
    });
});
