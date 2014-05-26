#include <bandit/bandit.h>

#include "TestConstants.h"
#include "core/Vec2.h"

using namespace bandit;

go_bandit([]()
{
    describe("a Vec2", []()
    {
        it("defaults to the origin", []()
        {
            Vec2 coord;

            AssertThat(coord.getX(), Is().EqualToWithDelta(0.0, FLOAT_EPSILON));
            AssertThat(coord.getY(), Is().EqualToWithDelta(0.0, FLOAT_EPSILON));
        });

        it("accepts two floats that specify its position", []()
        {
            Vec2 coord(5.0, 6.0);

            AssertThat(coord.getX(), Is().EqualToWithDelta(5.0, FLOAT_EPSILON));
            AssertThat(coord.getY(), Is().EqualToWithDelta(6.0, FLOAT_EPSILON));
        });

        it("accepts updates to its position", []()
        {
            Vec2 coord(32.0, 126.0);

            AssertThat(coord.getX(), Is().EqualToWithDelta(32.0, FLOAT_EPSILON));
            AssertThat(coord.getY(), Is().EqualToWithDelta(126.0, FLOAT_EPSILON));

            coord.setX(13.0);
            coord.setY(43.0);

            AssertThat(coord.getX(), Is().EqualToWithDelta(13.0, FLOAT_EPSILON));
            AssertThat(coord.getY(), Is().EqualToWithDelta(43.0, FLOAT_EPSILON));
        });

        describe("the set of Vec2 operations", []()
        {
            it("calculates the distance between two Vec2", []()
            {
                Vec2 positionA(0.f, 0.f);
                Vec2 positionB(4.f, 3.f);

                AssertThat(positionA.distanceTo(positionB), Is().EqualToWithDelta(5.f, FLOAT_EPSILON));
            });
        });
    });

    describe("Vec2 operations", []()
    {
        describe("positively comparing two Vec2", []()
        {
            Vec2 first(25.f, 6.f);
            Vec2 second(25.f, 6.f);
            Vec2 third(5.f * 5.f, 6.f);
            Vec2 fourth(13.f, 12.f);
            Vec2 fifth(25.f, 6.1f);

            it("should return true when both Vec2 components are equal", [&]()
            {
                AssertThat(first == second, Is().EqualTo(true));
                AssertThat(first == third, Is().EqualTo(true));
            });

            it("should return false when both Vec2 components are not equal", [&]()
            {
                AssertThat(first == fourth, Is().EqualTo(false));
                AssertThat(first == fifth, Is().EqualTo(false));
            });
        });

        describe("negatively comparing two Vec2", []()
        {
            Vec2 first(25.f, 6.f);
            Vec2 second(25.f, 6.f);
            Vec2 third(5.f * 5.f, 6.f);
            Vec2 fourth(13.f, 12.f);
            Vec2 fifth(25.f, 6.1f);

            it("should return true when both Vec2 components are not equal", [&]()
            {
                AssertThat(first != fourth, Is().EqualTo(true));
                AssertThat(first != fifth, Is().EqualTo(true));
            });

            it("should return false when both Vec2 components are equal", [&]()
            {
                AssertThat(first != second, Is().EqualTo(false));
                AssertThat(first != third, Is().EqualTo(false));
            });
        });


        describe("negating a Vec2", []()
        {
            it("should result in the Vec2 having negated x and y components", []()
            {
                Vec2 someVec1 = Vec2(3.f, 4.f);
                Vec2 negatedVec1 = -someVec1;
                AssertThat(negatedVec1.getX(), Is().EqualToWithDelta(-3.f, FLOAT_EPSILON));
                AssertThat(negatedVec1.getY(), Is().EqualToWithDelta(-4.f, FLOAT_EPSILON));

                Vec2 someVec2 = Vec2(-4.f, -3.f);
                Vec2 negatedVec2 = -someVec2;
                AssertThat(negatedVec2.getX(), Is().EqualToWithDelta(4.f, FLOAT_EPSILON));
                AssertThat(negatedVec2.getY(), Is().EqualToWithDelta(3.f, FLOAT_EPSILON));
            });
        });

        describe("normalising a Vec2", []()
        {
            it("should result in the Vec2 having a magnitude of 1", []()
            {
                Vec2 someVec1 = Vec2(3.f, 4.f);
                someVec1.normalise();
                AssertThat(someVec1.getMagnitude(), Is().EqualToWithDelta(1.f, FLOAT_EPSILON));
                AssertThat(someVec1.getX(), Is().EqualToWithDelta(0.6f, FLOAT_EPSILON));
                AssertThat(someVec1.getY(), Is().EqualToWithDelta(0.8f, FLOAT_EPSILON));

                Vec2 someVec2 = Vec2(-4.f, -3.f);
                someVec2.normalise();
                AssertThat(someVec2.getMagnitude(), Is().EqualToWithDelta(1.f, FLOAT_EPSILON));
                AssertThat(someVec2.getX(), Is().EqualToWithDelta(-0.8f, FLOAT_EPSILON));
                AssertThat(someVec2.getY(), Is().EqualToWithDelta(-0.6f, FLOAT_EPSILON));
            });
        });

        describe("getting a normalised copy of a Vec2", []()
        {
            it("should result in a new Vec2 with a magnitude of 1", []()
            {
                Vec2 someVec1 = Vec2(3.f, 4.f);
                Vec2 normalised1 = someVec1.getNormalised();
                AssertThat(normalised1.getMagnitude(), Is().EqualToWithDelta(1.f, FLOAT_EPSILON));
                AssertThat(normalised1.getX(), Is().EqualToWithDelta(0.6f, FLOAT_EPSILON));
                AssertThat(normalised1.getY(), Is().EqualToWithDelta(0.8f, FLOAT_EPSILON));

                Vec2 someVec2 = Vec2(-4.f, -3.f);
                Vec2 normalised2 = someVec2.getNormalised();
                AssertThat(normalised2.getMagnitude(), Is().EqualToWithDelta(1.f, FLOAT_EPSILON));
                AssertThat(normalised2.getX(), Is().EqualToWithDelta(-0.8f, FLOAT_EPSILON));
                AssertThat(normalised2.getY(), Is().EqualToWithDelta(-0.6f, FLOAT_EPSILON));
            });
        });

        describe("finding the magnitude of a Vec2", []()
        {
            it("should obey Pythagoras' theorem", []()
            {
                Vec2 test1 = Vec2(0.f, 0.f);
                Vec2 test2 = Vec2(3.f, 4.f);
                Vec2 test3 = Vec2(-12.f, 5.f);

                AssertThat(test1.getMagnitude(), Is().EqualToWithDelta(0.f, FLOAT_EPSILON));
                AssertThat(test2.getMagnitude(), Is().EqualToWithDelta(5.f, FLOAT_EPSILON));
                AssertThat(test3.getMagnitude(), Is().EqualToWithDelta(13.f, FLOAT_EPSILON));
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

                AssertThat(result1.getX(), Is().EqualToWithDelta(88.f, FLOAT_EPSILON));
                AssertThat(result1.getY(), Is().EqualToWithDelta(99.7f, FLOAT_EPSILON));

                AssertThat(result2.getX(), Is().EqualToWithDelta(-24.f, FLOAT_EPSILON));
                AssertThat(result2.getY(), Is().EqualToWithDelta(-1.f, FLOAT_EPSILON));

                AssertThat(result3.getX(), Is().EqualToWithDelta(-21.3f, FLOAT_EPSILON));
                AssertThat(result3.getY(), Is().EqualToWithDelta(24.7f, FLOAT_EPSILON));

                origin += target4;

                AssertThat(origin.getX(), Is().EqualToWithDelta(2.f, FLOAT_EPSILON));
                AssertThat(origin.getY(), Is().EqualToWithDelta(1.f, FLOAT_EPSILON));
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

                AssertThat(offset1.getX(), Is().EqualToWithDelta(-10.f, FLOAT_EPSILON));
                AssertThat(offset1.getY(), Is().EqualToWithDelta(-12.f, FLOAT_EPSILON));

                AssertThat(offset2.getX(), Is().EqualToWithDelta(-9.f, FLOAT_EPSILON));
                AssertThat(offset2.getY(), Is().EqualToWithDelta(213.f, FLOAT_EPSILON));

                AssertThat(offset3.getX(), Is().EqualToWithDelta(0.19f, FLOAT_EPSILON));
                AssertThat(offset3.getY(), Is().EqualToWithDelta(87.f, FLOAT_EPSILON));

                AssertThat(offset4.getX(), Is().EqualToWithDelta(1241.f, FLOAT_EPSILON));
                AssertThat(offset4.getY(), Is().EqualToWithDelta(-3.f, FLOAT_EPSILON));

                AssertThat(offset5.getX(), Is().EqualToWithDelta(-0.f, FLOAT_EPSILON));
                AssertThat(offset5.getY(), Is().EqualToWithDelta(-0.f, FLOAT_EPSILON));

                AssertThat(origin.getX(), Is().EqualToWithDelta(-10.f, FLOAT_EPSILON));
                AssertThat(origin.getY(), Is().EqualToWithDelta(-15.f, FLOAT_EPSILON));
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

                AssertThat(scaled1.getX(), Is().EqualToWithDelta(26.55f, FLOAT_EPSILON));
                AssertThat(scaled1.getY(), Is().EqualToWithDelta(15.5f, FLOAT_EPSILON));

                AssertThat(scaled2.getX(), Is().EqualToWithDelta(531.f, FLOAT_EPSILON));
                AssertThat(scaled2.getY(), Is().EqualToWithDelta(310.f, FLOAT_EPSILON));

                AssertThat(source.getX(), Is().EqualToWithDelta(53.1f, FLOAT_EPSILON));
                AssertThat(source.getY(), Is().EqualToWithDelta(31.0f, FLOAT_EPSILON));
            });

            it("should scale both components of the Vec2 DOWN by the scale factor", [&]()
            {
                Vec2 source = Vec2(5.31f, 3.1f);

                Vec2 scaled3 = source / 10;
                Vec2 scaled4 = source / 2;

                source /= 3;

                AssertThat(scaled3.getX(), Is().EqualToWithDelta(0.531f, FLOAT_EPSILON));
                AssertThat(scaled3.getY(), Is().EqualToWithDelta(0.31f, FLOAT_EPSILON));

                AssertThat(scaled4.getX(), Is().EqualToWithDelta(2.655f, FLOAT_EPSILON));
                AssertThat(scaled4.getY(), Is().EqualToWithDelta(1.55f, FLOAT_EPSILON));

                AssertThat(source.getX(), Is().EqualToWithDelta(1.77f, FLOAT_EPSILON));
                AssertThat(source.getY(), Is().EqualToWithDelta(1.033333333f, FLOAT_EPSILON));
            });
        });
    });
});
