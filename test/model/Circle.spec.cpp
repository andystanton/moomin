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
            Circle * circle = new Circle(50, 100);

            AssertThat(dynamic_cast<Entity *>(circle), Fulfills(IsInstanceOfEntity()));
        });
    });
});
