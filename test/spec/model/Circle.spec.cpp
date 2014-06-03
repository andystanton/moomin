#include <bandit/bandit.h>

#include "TestConstants.hpp"
#include "core/Core.hpp"
#include "model/Circle.hpp"
#include "drawing/Mesh.hpp"

using namespace bandit;

go_bandit([]()
{
    describe("a Circle", []()
    {
        it("is a subclass of Entity", []()
        {
            Entity * circle = new Circle(Vec2(50.f, 100.f), 10.f);

            AssertThat(circle->getPos(), Is().EqualTo(Vec2(50.f, 100.f)));
        });

        it("accepts a position and a radius", []()
        {
            Circle circle = Circle(Vec2(50.4f, 100.f), 10.f);

            AssertThat(circle.getPos(), Is().EqualTo(Vec2(50.4f, 100.f)));
            AssertThat(circle.getRadius(), Is().EqualToWithDelta(10.f, FLOAT_EPSILON));
        });
    });
});
