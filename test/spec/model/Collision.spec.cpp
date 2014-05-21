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
        AABB primary(       0.f,   0.f, 40.f, 30.f);

        AABB secondaryA( -36.f, -27.f, 40.f, 30.f);
        AABB secondaryB(  20.f,  25.f, 10.f, 10.f);
        AABB secondaryC(  35.f,  25.f, 40.f, 30.f);
        AABB secondaryD(  20.f,  -5.f, 10.f, 10.f);
        AABB secondaryE( -15.f,  10.f, 20.f, 10.f);
        AABB secondaryF(  37.f,  20.f,  5.f,  5.f);
        AABB secondaryG(   1.f,   1.f,  5.f,  5.f);

        Collision collisionA(primary, secondaryA);
        Collision collisionB(primary, secondaryB);
        Collision collisionC(primary, secondaryC);
        Collision collisionD(primary, secondaryD);
        Collision collisionE(primary, secondaryE);
        Collision collisionF(primary, secondaryF);
        Collision collisionG(primary, secondaryG);

        float tolerance = 0.00001;

        it("has primary and secondary AABBs", [&]() 
        {
            AssertThat(&collisionA.getPrimary(),   Is().EqualTo(&primary));
            AssertThat(&collisionA.getSecondary(), Is().EqualTo(&secondaryA));

            AssertThat(&collisionB.getPrimary(),   Is().EqualTo(&primary));
            AssertThat(&collisionB.getSecondary(), Is().EqualTo(&secondaryB));

            AssertThat(&collisionC.getPrimary(),   Is().EqualTo(&primary));
            AssertThat(&collisionC.getSecondary(), Is().EqualTo(&secondaryC));

            AssertThat(&collisionD.getPrimary(),   Is().EqualTo(&primary));
            AssertThat(&collisionD.getSecondary(), Is().EqualTo(&secondaryD));

            AssertThat(&collisionE.getPrimary(),   Is().EqualTo(&primary));
            AssertThat(&collisionE.getSecondary(), Is().EqualTo(&secondaryE));

            AssertThat(&collisionF.getPrimary(),   Is().EqualTo(&primary));
            AssertThat(&collisionF.getSecondary(), Is().EqualTo(&secondaryF));

            AssertThat(&collisionG.getPrimary(),   Is().EqualTo(&primary));
            AssertThat(&collisionG.getSecondary(), Is().EqualTo(&secondaryG));
        });

        it("records the depth of the Collision", [&]()
        {
            AssertThat(collisionA.getDepth(), Is().EqualTo(3.f));
            AssertThat(collisionB.getDepth(), Is().EqualTo(5.f));
            AssertThat(collisionC.getDepth(), Is().EqualToWithDelta(sqrt(50.f), tolerance));
            AssertThat(collisionD.getDepth(), Is().EqualTo(5.f));
            AssertThat(collisionE.getDepth(), Is().EqualTo(5.f));
            AssertThat(collisionF.getDepth(), Is().EqualTo(3.f));
            AssertThat(collisionG.getDepth(), Is().EqualToWithDelta(sqrt(72.f), tolerance));
        });

        it("calculates the escape translation for the primary AABB", [&]()
        {
            AssertThat(collisionA.getEscapeTranslation().getX(), Is().EqualToWithDelta(0.f, tolerance));
            AssertThat(collisionA.getEscapeTranslation().getY(), Is().EqualToWithDelta(3.f, tolerance));

            AssertThat(collisionB.getEscapeTranslation().getX(), Is().EqualToWithDelta( 0.f, tolerance));
            AssertThat(collisionB.getEscapeTranslation().getY(), Is().EqualToWithDelta(-5.f, tolerance));

            AssertThat(collisionC.getEscapeTranslation().getX(), Is().EqualToWithDelta(-5.f, tolerance));
            AssertThat(collisionC.getEscapeTranslation().getY(), Is().EqualToWithDelta(-5.f, tolerance));

            AssertThat(collisionD.getEscapeTranslation().getX(), Is().EqualToWithDelta( 0.f, tolerance));
            AssertThat(collisionD.getEscapeTranslation().getY(), Is().EqualToWithDelta( 5.f, tolerance));

            AssertThat(collisionE.getEscapeTranslation().getX(), Is().EqualToWithDelta( 5.f, tolerance));
            AssertThat(collisionE.getEscapeTranslation().getY(), Is().EqualToWithDelta( 0.f, tolerance));

            AssertThat(collisionF.getEscapeTranslation().getX(), Is().EqualToWithDelta(-3.f, tolerance));
            AssertThat(collisionF.getEscapeTranslation().getY(), Is().EqualToWithDelta( 0.f, tolerance));

            AssertThat(collisionG.getEscapeTranslation().getX(), Is().EqualToWithDelta( 6.f, tolerance));
            AssertThat(collisionG.getEscapeTranslation().getY(), Is().EqualToWithDelta( 6.f, tolerance));
        });
    });
});
