#include <bandit/bandit.h>
#include <gmock/gmock.h>

#include "GmockBDDAliases.h"

#include <cmath>

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

        AABB primaryB(      0.f,  0.f, 40.f, 30.f);
        AABB secondaryB(   20.f, 25.f, 10.f, 10.f);

        AABB primaryC(     0.f,   0.f, 40.f, 30.f);
        AABB secondaryC(  35.f,  25.f, 40.f, 30.f);

        Collision collisionA(primaryA, secondaryA);
        Collision collisionB(primaryB, secondaryB);
        Collision collisionC(primaryC, secondaryC);

        float tolerance = 0.00001;

        it("has primary and secondary AABBs", [&]() 
        {
            AssertThat(&collisionA.getPrimary(),   Is().EqualTo(&primaryA));
            AssertThat(&collisionA.getSecondary(), Is().EqualTo(&secondaryA));

            AssertThat(&collisionB.getPrimary(),   Is().EqualTo(&primaryB));
            AssertThat(&collisionB.getSecondary(), Is().EqualTo(&secondaryB));

            AssertThat(&collisionC.getPrimary(),   Is().EqualTo(&primaryC));
            AssertThat(&collisionC.getSecondary(), Is().EqualTo(&secondaryC));
        });

        it("records the depth of the Collision", [&]()
        {
            AssertThat(collisionA.getDepth(), Is().EqualTo(3.f));
            AssertThat(collisionB.getDepth(), Is().EqualTo(5.f));
            AssertThat(collisionC.getDepth(), Is().EqualToWithDelta(sqrt(50), tolerance));
        });

        it("calculates the escape translation for the primary AABB", [&]()
        {
            AssertThat(collisionA.getEscapeTranslation().getX(), Is().EqualToWithDelta(4.f, tolerance));
            AssertThat(collisionA.getEscapeTranslation().getY(), Is().EqualToWithDelta(0.f, tolerance));

            AssertThat(collisionB.getEscapeTranslation().getX(), Is().EqualToWithDelta( 0.f, tolerance));
            AssertThat(collisionB.getEscapeTranslation().getY(), Is().EqualToWithDelta(-5.f, tolerance));            

            AssertThat(collisionC.getEscapeTranslation().getX(), Is().EqualToWithDelta(-5.f, tolerance));
            AssertThat(collisionC.getEscapeTranslation().getY(), Is().EqualToWithDelta(-5.f, tolerance));            
        });
    });
});
