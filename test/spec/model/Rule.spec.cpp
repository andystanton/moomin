#include <bandit/bandit.h>

#include "model/Rule.hpp"
#include "model/rules/DirectionAccelerationRule.hpp"
#include "model/Circle.hpp"
#include "core/Vec2.hpp"

#include "mock/MockEntity.hpp"

using namespace bandit;

go_bandit([]()
{
    describe("a Rule", []()
    {
        it("affects an Entity with a time delta in ms", []()
        {
            Rule * gravity = new DirectionAccelerationRule(Vec2(0.f, -10.f));
            Entity * entity = new Circle(Vec2(100.f, 100.f), 10.f);

            gravity->apply(*entity, 100.f);
        });
    });
});
