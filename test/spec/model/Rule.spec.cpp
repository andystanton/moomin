#include <bandit/bandit.h>

#include "model/Rule.h"
#include "model/rules/DirectionAccelerationRule.h"
#include "model/Circle.h"
#include "core/Vec2.h"

#include "mock/MockEntity.h"

using namespace bandit;

go_bandit([]() 
{
    describe("a Rule", []() 
    {
        it("affects an Entity with a time delta in ms", []()
        {
            Rule * gravity = new DirectionAccelerationRule(Vec2(0.f, -10.f));
            Entity * entity = new Circle(100.f, 100.f, 10.f);

            gravity->apply(*entity, 100.f);
        });
    });
});
