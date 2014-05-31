#include <bandit/bandit.h>
#include <gmock/gmock.h>

#include "GmockBDDAliases.h"
#include "TestConstants.h"

#include <cmath>

#include "model/Entity.h"
#include "model/Collision.h"
#include "model/Circle.h"
#include "model/AABB.h"

using namespace bandit;

using ::testing::Ref;

go_bandit([]()
{
    describe("Collisions", []()
    {
        describe("a Collision between two Circles", []()
        {
            Circle primaryA(0.f, 0.f, 3.f);
            Circle secondaryA(4.f, 3.f, 3.f);

            Collision collisionA(primaryA, secondaryA);

            Circle primaryB(0.f, 0.f, 3.f);
            Circle secondaryB(-4.f, -3.f, 3.f);

            Collision collisionB(primaryB, secondaryB);

            it("has primary and secondary Circles", [&]()
            {
                AssertThat(&collisionA.getPrimary(), Is().EqualTo(&primaryA));
                AssertThat(&collisionA.getSecondary(), Is().EqualTo(&secondaryA));

                AssertThat(&collisionB.getPrimary(), Is().EqualTo(&primaryB));
                AssertThat(&collisionB.getSecondary(), Is().EqualTo(&secondaryB));
            });

            it("records the depth of the Collision", [&]()
            {
                AssertThat(collisionA.getDepth(), Is().EqualToWithDelta(1.f, FLOAT_EPSILON));
                AssertThat(collisionB.getDepth(), Is().EqualToWithDelta(1.f, FLOAT_EPSILON));
            });

            it("calculates the escape translation for the primary Circle", [&]()
            {
                AssertThat(collisionA.getEscapeTranslation(), Is().EqualTo(Vec2(-0.4, -0.3)));
            });
        });

        describe("a Collision between two AABBs", []()
        {
            AABB primary(      0.f,   0.f, 40.f, 30.f);

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
                AssertThat(collisionA.getDepth(), Is().EqualToWithDelta(3.f, FLOAT_EPSILON));
                AssertThat(collisionB.getDepth(), Is().EqualToWithDelta(5.f, FLOAT_EPSILON));
                AssertThat(collisionC.getDepth(), Is().EqualToWithDelta(sqrt(50.f), FLOAT_EPSILON));
                AssertThat(collisionD.getDepth(), Is().EqualToWithDelta(5.f, FLOAT_EPSILON));
                AssertThat(collisionE.getDepth(), Is().EqualToWithDelta(5.f, FLOAT_EPSILON));
                AssertThat(collisionF.getDepth(), Is().EqualToWithDelta(3.f, FLOAT_EPSILON));
                AssertThat(collisionG.getDepth(), Is().EqualToWithDelta(sqrt(72.f), FLOAT_EPSILON));
            });

            it("calculates the escape translation for the primary AABB", [&]()
            {
                AssertThat(collisionA.getEscapeTranslation(), Is().EqualTo(Vec2( 0.f,  1.5f)));
                AssertThat(collisionB.getEscapeTranslation(), Is().EqualTo(Vec2( 0.f, -2.5f)));
                AssertThat(collisionC.getEscapeTranslation(), Is().EqualTo(Vec2(-2.5f,-2.5f)));
                AssertThat(collisionD.getEscapeTranslation(), Is().EqualTo(Vec2( 0.f,  2.5f)));
                AssertThat(collisionE.getEscapeTranslation(), Is().EqualTo(Vec2( 2.5f, 0.f)));
                AssertThat(collisionF.getEscapeTranslation(), Is().EqualTo(Vec2(-1.5f, 0.f)));
                AssertThat(collisionG.getEscapeTranslation(), Is().EqualTo(Vec2( 3.f,  3.f)));
            });
        });

        describe("a Collision between a Circle and an AABB", []()
        {
            AABB secondary(-10.f, -10.f, 20.f, 20.f);
            Circle primaryA(  0.f,  10.f, 3.f);
            Circle primaryB(  0.f, -10.f, 4.f);
            Circle primaryC(-10.f,   0.f, 2.5f);
            Circle primaryD( 10.f,   0.f, 1.5f);
            Circle primaryE(-10.f,  10.f, 1.15f);
            Circle primaryF( 10.f,  10.f, 1.25f);
            Circle primaryG( 10.f, -10.f, 1.35f);
            Circle primaryH(-10.f, -10.f, 1.45f);
            Circle primaryI(100.f, 100.f,20.f);

            Collision collisionA(primaryA, secondary);
            Collision collisionB(primaryB, secondary);
            Collision collisionC(primaryC, secondary);
            Collision collisionD(primaryD, secondary);
            Collision collisionE(primaryE, secondary);
            Collision collisionF(primaryF, secondary);
            Collision collisionG(primaryG, secondary);
            Collision collisionH(primaryH, secondary);
            Collision collisionI(primaryI, secondary);

            it("has a primary Circle and a primary AABB", [&]()
            {
                AssertThat(&collisionA.getPrimary(), Is().EqualTo(&primaryA));
                AssertThat(&collisionA.getSecondary(), Is().EqualTo(&secondary));

                AssertThat(&collisionB.getPrimary(), Is().EqualTo(&primaryB));
                AssertThat(&collisionB.getSecondary(), Is().EqualTo(&secondary));

                AssertThat(&collisionC.getPrimary(), Is().EqualTo(&primaryC));
                AssertThat(&collisionC.getSecondary(), Is().EqualTo(&secondary));

                AssertThat(&collisionD.getPrimary(), Is().EqualTo(&primaryD));
                AssertThat(&collisionD.getSecondary(), Is().EqualTo(&secondary));

                AssertThat(&collisionE.getPrimary(), Is().EqualTo(&primaryE));
                AssertThat(&collisionE.getSecondary(), Is().EqualTo(&secondary));

                AssertThat(&collisionF.getPrimary(), Is().EqualTo(&primaryF));
                AssertThat(&collisionF.getSecondary(), Is().EqualTo(&secondary));

                AssertThat(&collisionG.getPrimary(), Is().EqualTo(&primaryG));
                AssertThat(&collisionG.getSecondary(), Is().EqualTo(&secondary));

                AssertThat(&collisionH.getPrimary(), Is().EqualTo(&primaryH));
                AssertThat(&collisionH.getSecondary(), Is().EqualTo(&secondary));

                AssertThat(&collisionI.getPrimary(), Is().EqualTo(&primaryI));
                AssertThat(&collisionI.getSecondary(), Is().EqualTo(&secondary));
            });

            it("records the depth of the Collision", [&]()
            {
                AssertThat(collisionA.getDepth(), Is().EqualToWithDelta(3.f,   FLOAT_EPSILON));
                AssertThat(collisionB.getDepth(), Is().EqualToWithDelta(4.f,   FLOAT_EPSILON));
                AssertThat(collisionC.getDepth(), Is().EqualToWithDelta(2.5f,  FLOAT_EPSILON));
                AssertThat(collisionD.getDepth(), Is().EqualToWithDelta(1.5f,  FLOAT_EPSILON));
                AssertThat(collisionE.getDepth(), Is().EqualToWithDelta(1.15f, FLOAT_EPSILON));
                AssertThat(collisionF.getDepth(), Is().EqualToWithDelta(1.25f, FLOAT_EPSILON));
                AssertThat(collisionG.getDepth(), Is().EqualToWithDelta(1.35f, FLOAT_EPSILON));
                AssertThat(collisionH.getDepth(), Is().EqualToWithDelta(1.45f, FLOAT_EPSILON));
                AssertThat(collisionI.getDepth(), Is().EqualToWithDelta(0.f,   FLOAT_EPSILON));
            });

            it("calculates the escape translation for the primary AABB", [&]()
            {
                AssertThat(collisionA.getEscapeTranslation(), Is().EqualTo(Vec2( 0.f,   1.5f)));
                AssertThat(collisionB.getEscapeTranslation(), Is().EqualTo(Vec2( 0.f,  -2.f)));
                AssertThat(collisionC.getEscapeTranslation(), Is().EqualTo(Vec2(-1.25f, 0.f)));
                AssertThat(collisionD.getEscapeTranslation(), Is().EqualTo(Vec2( 0.75f, 0.f)));
                AssertThat(collisionE.getEscapeTranslation(), Is().EqualTo(Vec2(-0.4065863f,  0.4065863f)));
                AssertThat(collisionF.getEscapeTranslation(), Is().EqualTo(Vec2( 0.4419417f,  0.4419417f)));
                AssertThat(collisionG.getEscapeTranslation(), Is().EqualTo(Vec2( 0.4772970f, -0.4772970f)));
                AssertThat(collisionH.getEscapeTranslation(), Is().EqualTo(Vec2(-0.5126524f, -0.5126524f)));
            });
        });

        describe("a Collision between an AABB and a Circle", []()
        {
            AABB primary(-10.f, -10.f, 20.f, 20.f);
            Circle secondaryA(  0.f,  10.f, 3.f);
            Circle secondaryB(  0.f, -10.f, 4.f);
            Circle secondaryC(-10.f,   0.f, 2.5f);
            Circle secondaryD( 10.f,   0.f, 1.5f);
            Circle secondaryE(-10.f,  10.f, 1.15f);
            Circle secondaryF( 10.f,  10.f, 1.25f);
            Circle secondaryG( 10.f, -10.f, 1.35f);
            Circle secondaryH(-10.f, -10.f, 1.45f);
            Circle secondaryI(100.f, 100.f,20.f);
            Circle secondaryJ( 15.f,  15.f, 10.f);
            Circle secondaryK( 15.f,  12.f, 10.f);

            Collision collisionA(primary, secondaryA);
            Collision collisionB(primary, secondaryB);
            Collision collisionC(primary, secondaryC);
            Collision collisionD(primary, secondaryD);
            Collision collisionE(primary, secondaryE);
            Collision collisionF(primary, secondaryF);
            Collision collisionG(primary, secondaryG);
            Collision collisionH(primary, secondaryH);
            Collision collisionI(primary, secondaryI);
            Collision collisionJ(primary, secondaryJ);
            Collision collisionK(primary, secondaryK);

            it("has a primary AABB and a secondary Circle", [&]()
            {
                AssertThat(&collisionA.getPrimary(), Is().EqualTo(&primary));
                AssertThat(&collisionA.getSecondary(), Is().EqualTo(&secondaryA));

                AssertThat(&collisionB.getPrimary(), Is().EqualTo(&primary));
                AssertThat(&collisionB.getSecondary(), Is().EqualTo(&secondaryB));

                AssertThat(&collisionC.getPrimary(), Is().EqualTo(&primary));
                AssertThat(&collisionC.getSecondary(), Is().EqualTo(&secondaryC));

                AssertThat(&collisionD.getPrimary(), Is().EqualTo(&primary));
                AssertThat(&collisionD.getSecondary(), Is().EqualTo(&secondaryD));

                AssertThat(&collisionE.getPrimary(), Is().EqualTo(&primary));
                AssertThat(&collisionE.getSecondary(), Is().EqualTo(&secondaryE));

                AssertThat(&collisionF.getPrimary(), Is().EqualTo(&primary));
                AssertThat(&collisionF.getSecondary(), Is().EqualTo(&secondaryF));

                AssertThat(&collisionG.getPrimary(), Is().EqualTo(&primary));
                AssertThat(&collisionG.getSecondary(), Is().EqualTo(&secondaryG));

                AssertThat(&collisionH.getPrimary(), Is().EqualTo(&primary));
                AssertThat(&collisionH.getSecondary(), Is().EqualTo(&secondaryH));

                AssertThat(&collisionI.getPrimary(), Is().EqualTo(&primary));
                AssertThat(&collisionI.getSecondary(), Is().EqualTo(&secondaryI));

                AssertThat(&collisionJ.getPrimary(), Is().EqualTo(&primary));
                AssertThat(&collisionJ.getSecondary(), Is().EqualTo(&secondaryJ));

                AssertThat(&collisionK.getPrimary(), Is().EqualTo(&primary));
                AssertThat(&collisionK.getSecondary(), Is().EqualTo(&secondaryK));
            });

            it("records the depth of the Collision", [&]()
            {
                AssertThat(collisionA.getDepth(), Is().EqualToWithDelta(3.f,   FLOAT_EPSILON));
                AssertThat(collisionB.getDepth(), Is().EqualToWithDelta(4.f,   FLOAT_EPSILON));
                AssertThat(collisionC.getDepth(), Is().EqualToWithDelta(2.5f,  FLOAT_EPSILON));
                AssertThat(collisionD.getDepth(), Is().EqualToWithDelta(1.5f,  FLOAT_EPSILON));
                AssertThat(collisionE.getDepth(), Is().EqualToWithDelta(1.15f, FLOAT_EPSILON));
                AssertThat(collisionF.getDepth(), Is().EqualToWithDelta(1.25f, FLOAT_EPSILON));
                AssertThat(collisionG.getDepth(), Is().EqualToWithDelta(1.35f, FLOAT_EPSILON));
                AssertThat(collisionH.getDepth(), Is().EqualToWithDelta(1.45f, FLOAT_EPSILON));
                AssertThat(collisionI.getDepth(), Is().EqualToWithDelta(0.f,   FLOAT_EPSILON));
                AssertThat(collisionJ.getDepth(), Is().EqualToWithDelta(5.f,   FLOAT_EPSILON));
            });

            it("calculates the escape translation for the primary AABB", [&]()
            {
                AssertThat(collisionA.getEscapeTranslation(), Is().EqualTo(Vec2( 0.f,  -1.5f)));
                AssertThat(collisionB.getEscapeTranslation(), Is().EqualTo(Vec2( 0.f,   2.f)));
                AssertThat(collisionC.getEscapeTranslation(), Is().EqualTo(Vec2( 1.25f, 0.f)));
                AssertThat(collisionD.getEscapeTranslation(), Is().EqualTo(Vec2(-0.75f, 0.f)));
                AssertThat(collisionE.getEscapeTranslation(), Is().EqualTo(Vec2( 0.4065863f, -0.4065863f)));
                AssertThat(collisionF.getEscapeTranslation(), Is().EqualTo(Vec2(-0.4419417f, -0.4419417f)));
                AssertThat(collisionG.getEscapeTranslation(), Is().EqualTo(Vec2(-0.4772970f,  0.4772970f)));
                AssertThat(collisionH.getEscapeTranslation(), Is().EqualTo(Vec2( 0.5126524f,  0.5126524f)));
                AssertThat(collisionI.getEscapeTranslation(), Is().EqualTo(Vec2(0, 0)));
                AssertThat(collisionJ.getEscapeTranslation(), Is().EqualTo(Vec2(-1.7677669f, -1.7677669f)));
                //AssertThat(collisionK.getEscapeTranslation(), Is().EqualTo(Vec2(-1.7677669f, -1.7677669f)));
            });
        });
    });
});
