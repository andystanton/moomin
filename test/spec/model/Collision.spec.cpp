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
        Entity primaryA = Circle(0.f, 0.f, 3.f);
        Entity secondaryA = Circle(4.f, 3.f, 3.f);
        Collision collisionA(primaryA, secondaryA);

        Entity primaryB = Circle(0.f, 0.f, 3.f);
        Entity secondaryB = Circle(-4.f, -3.f, 3.f);
        Collision collisionB(primaryB, secondaryB);

        it("has primary and secondary entities", [&]() 
        {
            AssertThat(&collisionA.getPrimary(), Is().EqualTo(&primaryA));
            AssertThat(&collisionA.getSecondary(), Is().EqualTo(&secondaryA));

            AssertThat(&collisionB.getPrimary(), Is().EqualTo(&primaryB));
            AssertThat(&collisionB.getSecondary(), Is().EqualTo(&secondaryB));
        });

        it("records the depth of the collision", [&]()
        {
            AssertThat(collisionA.getDepth(), Is().EqualTo(1.f));
            AssertThat(collisionB.getDepth(), Is().EqualTo(1.f));
        });
    });
});
