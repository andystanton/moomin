#include <bandit/bandit.h>
#include <gmock/gmock.h>

#include "GmockBDDAliases.h"

#include "model/Entity.h"
#include "model/Collision.h"
#include "model/Circle.h"

using namespace bandit;

using ::testing::Ref;

go_bandit([]() 
{
    describe("a Collision between two Circles", []() 
    {
        Entity primary = Circle(0.f, 0.f, 3.f);
        Entity secondary = Circle(4.f, 3.f, 3.f);
        Collision collision(primary, secondary);

        it("has primary and secondary entities", [&]() 
        {
            AssertThat(&collision.getPrimary(), Is().EqualTo(&primary));
            AssertThat(&collision.getSecondary(), Is().EqualTo(&secondary));
        });

        it("records the incursion of the primary into the secondary", [&]()
        {
            AssertThat(collision.getDepth(), Is().EqualTo(1.f));
        });
    });
});
