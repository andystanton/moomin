#include <bandit/bandit.h>

#include "TestConstants.h"
#include "core/Core.h"
#include "model/Circle.h"
#include "drawing/Mesh.h"

using namespace bandit;

go_bandit([]()
{
    describe("a Circle", []()
    {
        it("is a subclass of Entity", []()
        {
            Entity * circle = new Circle(50.f, 100.f, 10.f);

            AssertThat(circle->getPos().getX(), Is().EqualToWithDelta(50.f, FLOAT_EPSILON));
            AssertThat(circle->getPos().getY(), Is().EqualToWithDelta(100.f, FLOAT_EPSILON));
        });

        it("accepts a position and a radius", []()
        {
            Circle circle = Circle(50.4f, 100.f, 10.f);

            AssertThat(circle.getPos().getX(), Is().EqualToWithDelta(50.4f, FLOAT_EPSILON));
            AssertThat(circle.getPos().getY(), Is().EqualToWithDelta(100.f, FLOAT_EPSILON));
            AssertThat(circle.getRadius(), Is().EqualToWithDelta(10.f, FLOAT_EPSILON));
        });
    });
});
