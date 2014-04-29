#include <bandit/bandit.h>

#include "model/Rule.h"
#include "model/rules/AccelerationRule.h"
#include "core/Vec2.h"

using namespace bandit;

go_bandit([]() 
{
    describe("the Rules", []() 
    {
        describe("an Acceleration Rule", []()
        {
            it("is an instance of a Rule", []()
            {
                Rule * gravity = new AccelerationRule(Vec2(0.f, 10.f));
            });

            it("accepts a Vec2 as its argument", []() 
            {
                AccelerationRule gravity(Vec2(0.f, 10.f));

                AssertThat(gravity.getAcceleration().getX(), Is().EqualTo(0.f));
                AssertThat(gravity.getAcceleration().getY(), Is().EqualTo(10.f));
            });
        });
    });
});
