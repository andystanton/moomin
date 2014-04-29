#include <bandit/bandit.h>

#include "helper/CustomMatchers.h"

#include "core/Core.h"
#include "model/Entity.h"
#include "model/Circle.h"
#include "drawing/Mesh.h"

using namespace bandit;

go_bandit([]() 
{
    describe("a Circle", []() 
    {
        it("is a subclass of Entity", []() 
        {
            Circle * circle = new Circle(50.f, 100.f);

            AssertThat(dynamic_cast<Entity *>(circle), Fulfills(IsInstanceOfEntity()));
        });

        it("accepts a position", []()
        {
            Circle circle = Circle(50.4f, 100.f);

            AssertThat(circle.getPos().getX(), Is().EqualTo(50.4f));
            AssertThat(circle.getPos().getY(), Is().EqualTo(100.f));
        });
    });
});
