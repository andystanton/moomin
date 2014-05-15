#include <bandit/bandit.h>
#include <gmock/gmock.h>

#include "GmockBDDAliases.h"

#include "model/Entity.h"
#include "model/Collision.h"
#include "model/Circle.h"
#include "model/AABB.h"

using namespace bandit;

using ::testing::Ref;

go_bandit([]() 
{
    describe("a Collision between two Circles", []() 
    {
        Circle primaryA(0.f, 0.f, 3.f);
        Circle secondaryA(4.f, 3.f, 3.f);

        Collision collisionA(primaryA, secondaryA);

        Circle primaryB(0.f, 0.f, 3.f);
        Circle secondaryB(-4.f, -3.f, 3.f);

        Collision collisionB(primaryB, secondaryB);

        float tolerance = 0.00001;

        it("has primary and secondary Circles", [&]() 
        {
            AssertThat(&collisionA.getPrimary(), Is().EqualTo(&primaryA));
            AssertThat(&collisionA.getSecondary(), Is().EqualTo(&secondaryA));

            AssertThat(&collisionB.getPrimary(), Is().EqualTo(&primaryB));
            AssertThat(&collisionB.getSecondary(), Is().EqualTo(&secondaryB));
        });

        it("records the depth of the Collision", [&]()
        {
            AssertThat(collisionA.getDepth(), Is().EqualTo(1.f));
            AssertThat(collisionB.getDepth(), Is().EqualTo(1.f));
        });

        it("calculates the escape translation for the primary Circle", [&]()
        {
            AssertThat(collisionA.getEscapeTranslation().getX(), Is().EqualToWithDelta(-0.4, tolerance));
            AssertThat(collisionA.getEscapeTranslation().getY(), Is().EqualToWithDelta(-0.3, tolerance));
        });
    });

    describe("a Collision between two AABBs", []()
    {
        AABB primaryA(     0.f,   0.f, 40.f, 30.f);
        AABB secondaryA( -36.f, -27.f, 40.f, 30.f);

        Collision collisionA(primaryA, secondaryA);

        it("has primary and secondary AABBs", [&]() 
        {
            AssertThat(&collisionA.getPrimary(), Is().EqualTo(&primaryA));
            AssertThat(&collisionA.getSecondary(), Is().EqualTo(&secondaryA));
        });

        it("records the depth of the Collision", [&]()
        {
            //AssertThat(collisionA.getDepth(), Is().EqualTo(5.f));
        });
    });
});
