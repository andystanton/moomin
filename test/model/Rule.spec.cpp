#include <bandit/bandit.h>

#include "model/Rule.h"
#include "model/rules/AccelerationRule.h"
#include "model/rules/BoundingRule.h"

#include "core/Vec2.h"

using namespace bandit;

go_bandit([]() 
{
    describe("the Rules", []() 
    {
        it("returns a new Vec2 when applied to a Vec2 with a time delta in ms", []()
        {
            Rule * gravity = new AccelerationRule(Vec2(0.f, -10.f));
            Vec2 originalVelocity(100.f, 0.f);
            Vec2 modifiedVelocity = gravity->apply(originalVelocity, 100.f);
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

            it("applies its acceleration to a Vec2 given a time delta in ms", []() 
            {
                // set gravity to (0, -10) units/second^2
                AccelerationRule gravity(Vec2(0.f, -10.f));

                // set initial velocity to (0, 0)
                Vec2 originalVelocity = Vec2(0.f, 0.f);

                float timeDeltaMilliseconds = 100;

                // after 100ms, assert the expected change in velocity
                Vec2 modifiedVelocity1 = gravity.apply(originalVelocity, timeDeltaMilliseconds);

                AssertThat(modifiedVelocity1.getX(), Is().EqualTo(0.f));
                AssertThat(modifiedVelocity1.getY(), Is().EqualTo(-1.f))

                // after another 100ms, assert the expected change in velocity
                Vec2 modifiedVelocity2 = gravity.apply(modifiedVelocity1, timeDeltaMilliseconds);
                
                AssertThat(modifiedVelocity2.getX(), Is().EqualTo(0.f));
                AssertThat(modifiedVelocity2.getY(), Is().EqualTo(-2.f))

                float longerTimeDeltaMilliseconds = 500;

                // this time increase delta to 500 ms
                Vec2 modifiedVelocity3 = gravity.apply(modifiedVelocity2, longerTimeDeltaMilliseconds);

                AssertThat(modifiedVelocity3.getX(), Is().EqualTo(0.f));
                AssertThat(modifiedVelocity3.getY(), Is().EqualTo(-7.f));
            });
        });

        describe("a Bounding Rule", []()
        {
            it("is an instance of a Rule", []()
            {
                Rule * area = new BoundingRule(Vec2(0.f, 0.f), Vec2(640.f, 480.f));
            });
        });
    });
});
