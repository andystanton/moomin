#include <bandit/bandit.h>

#include "core/Vec2.h"

using namespace bandit;

go_bandit([]()
{
    describe("a Vec2", []()
    {
        it("defaults to the origin", []()
        {
            Vec2 coord;

            AssertThat(coord.getX(), Is().EqualTo(0.0));
            AssertThat(coord.getY(), Is().EqualTo(0.0));
        });

        it("accepts two floats that specify its position", []()
        {
            Vec2 coord(5.0, 6.0);

            AssertThat(coord.getX(), Is().EqualTo(5.0));
            AssertThat(coord.getY(), Is().EqualTo(6.0));
        });

        it("accepts updates to its position", []()
        {
            Vec2 coord(32.0, 126.0);

            AssertThat(coord.getX(), Is().EqualTo(32.0));
            AssertThat(coord.getY(), Is().EqualTo(126.0));

            coord.setX(13.0);
            coord.setY(43.0);

            AssertThat(coord.getX(), Is().EqualTo(13.0));
            AssertThat(coord.getY(), Is().EqualTo(43.0));
        });

        describe("the set of Vec2 operations", []()
        {
            it("calculates the distance between two Vec2", []()
            {
                Vec2 positionA(0.f, 0.f);
                Vec2 positionB(4.f, 3.f);

                AssertThat(positionA.distanceTo(positionB), Is().EqualTo(5.f));
            });
        });
    });

    describe("Vec2 operations", []()
    {
        float threshold = 0.000001;

        describe("normalising a Vec2", []()
        {
            it("should result in a new Vec2 with a magnitude of 1", []()
            {
                Vec2 someVec1 = Vec2(3.f, 4.f);
                Vec2 normalised1 = someVec1.getNormalised();
                AssertThat(normalised1.getMagnitude(), Is().EqualTo(1.f));
                AssertThat(normalised1.getX(), Is().EqualTo(0.6f));
                AssertThat(normalised1.getY(), Is().EqualTo(0.8f));

                Vec2 someVec2 = Vec2(-4.f, -3.f);
                Vec2 normalised2 = someVec2.getNormalised();
                AssertThat(normalised2.getMagnitude(), Is().EqualTo(1.f));
                AssertThat(normalised2.getX(), Is().EqualTo(-0.8f));
                AssertThat(normalised2.getY(), Is().EqualTo(-0.6f));
            });
        });

        describe("finding the magnitude of a Vec2", []()
        {
            it("should obey Pythagoras' theorem", []()
            {
                Vec2 test1 = Vec2(0.f, 0.f);
                Vec2 test2 = Vec2(3.f, 4.f);
                Vec2 test3 = Vec2(-12.f, 5.f);

                AssertThat(test1.getMagnitude(), Is().EqualTo(0.f));
                AssertThat(test2.getMagnitude(), Is().EqualTo(5.f));
                AssertThat(test3.getMagnitude(), Is().EqualTo(13.f));
            });
        });

        describe("adding two Vec2 together", [&]()
        {
            it("should give the sum of the Vec2", [&]()
            {
                Vec2 origin = Vec2(-12.f, -0.3f);

                Vec2 target1 = Vec2(100.f, 100.f);
                Vec2 target2 = Vec2(-12.f, -0.7f);
                Vec2 target3 = Vec2(-9.3f, 25.f);
                Vec2 target4 = Vec2( 14.f, 1.3f);

                Vec2 result1 = origin + target1;
                Vec2 result2 = origin + target2;
                Vec2 result3 = origin + target3;

                AssertThat(result1.getX(), Is().EqualTo(88.f));
                AssertThat(result1.getY(), Is().EqualTo(99.7f));

                AssertThat(result2.getX(), Is().EqualTo(-24.f));
                AssertThat(result2.getY(), Is().EqualTo(-1.f));

                AssertThat(result3.getX(), Is().EqualTo(-21.3f));
                AssertThat(result3.getY(), Is().EqualTo(24.7f));

                origin += target4;

                AssertThat(origin.getX(), Is().EqualToWithDelta(2.f, threshold));
                AssertThat(origin.getY(), Is().EqualToWithDelta(1.f, threshold));
            });
        });

        describe("subtracting one Vec2 from another", [&]()
        {
            it("should give the position of the second relative to the first", [&]()
            {
                Vec2 origin = Vec2(0.f, 0.f);

                Vec2 target1 = Vec2(10.f, 12.f);
                Vec2 target2 = Vec2(9.f, -213.f);
                Vec2 target3 = Vec2(-0.19f, -87.f);
                Vec2 target4 = Vec2(-1241.f, 3.f);
                Vec2 target5 = Vec2(0.f, 0.f);
                Vec2 target6 = Vec2(10.f, 15.f);

                Vec2 offset1 = origin - target1;
                Vec2 offset2 = origin - target2;
                Vec2 offset3 = origin - target3;
                Vec2 offset4 = origin - target4;
                Vec2 offset5 = origin - target5;
                origin -= target6;

                AssertThat(offset1.getX(), Is().EqualTo(-10.f));
                AssertThat(offset1.getY(), Is().EqualTo(-12.f));

                AssertThat(offset2.getX(), Is().EqualTo(-9.f));
                AssertThat(offset2.getY(), Is().EqualTo(213.f));

                AssertThat(offset3.getX(), Is().EqualTo(0.19f));
                AssertThat(offset3.getY(), Is().EqualTo(87.f));

                AssertThat(offset4.getX(), Is().EqualTo(1241.f));
                AssertThat(offset4.getY(), Is().EqualTo(-3.f));

                AssertThat(offset5.getX(), Is().EqualTo(-0.f));
                AssertThat(offset5.getY(), Is().EqualTo(-0.f));

                AssertThat(origin.getX(), Is().EqualToWithDelta(-10.f, threshold));
                AssertThat(origin.getY(), Is().EqualToWithDelta(-15.f, threshold));
            });
        });

        describe("scaling a Vec2 by a constant scale factor", [&]()
        {
            it("should scale both components of the Vec2 UP by the scale factor", [&]()
            {
                Vec2 source = Vec2(5.31f, 3.1f);

                Vec2 scaled1 = source * 5;
                Vec2 scaled2 = 100 * source;

                source *= 10;

                AssertThat(scaled1.getX(), Is().EqualToWithDelta(26.55, threshold));
                AssertThat(scaled1.getY(), Is().EqualToWithDelta(15.5, threshold));

                AssertThat(scaled2.getX(), Is().EqualToWithDelta(531.f, threshold));
                AssertThat(scaled2.getY(), Is().EqualToWithDelta(310.f, threshold));

                AssertThat(source.getX(), Is().EqualToWithDelta(53.1f, threshold));
                AssertThat(source.getY(), Is().EqualToWithDelta(31.0f, threshold));
            });

            it("should scale both components of the Vec2 DOWN by the scale factor", [&]()
            {
                Vec2 source = Vec2(5.31f, 3.1f);

                Vec2 scaled3 = source / 10;
                Vec2 scaled4 = source / 2;

                source /= 3;

                AssertThat(scaled3.getX(), Is().EqualToWithDelta(0.531f, threshold));
                AssertThat(scaled3.getY(), Is().EqualToWithDelta(0.31f, threshold));

                AssertThat(scaled4.getX(), Is().EqualToWithDelta(2.655f, threshold));
                AssertThat(scaled4.getY(), Is().EqualToWithDelta(1.55f, threshold));

                AssertThat(source.getX(), Is().EqualToWithDelta(1.77f, threshold));
                AssertThat(source.getY(), Is().EqualToWithDelta(1.033333333f, threshold));
            });
        });
    });
});
