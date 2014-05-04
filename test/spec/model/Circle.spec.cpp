#include <bandit/bandit.h>

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

            AssertThat(circle->getPos().getX(), Is().EqualTo(50.f));
            AssertThat(circle->getPos().getY(), Is().EqualTo(100.f));
        });

        it("accepts a position and a radius", []()
        {
            Circle circle = Circle(50.4f, 100.f, 10.f);

            AssertThat(circle.getPos().getX(), Is().EqualTo(50.4f));
            AssertThat(circle.getPos().getY(), Is().EqualTo(100.f));
            AssertThat(circle.getRadius(), Is().EqualTo(10.f));
        });
    });
});
