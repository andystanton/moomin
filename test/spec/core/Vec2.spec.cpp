#include <bandit/bandit.h>

#include "TestConstants.hpp"
#include "core/Vec2.hpp"

using namespace bandit;

go_bandit([]()
{
    describe("a Vec2", []()
    {
        it("defaults to the origin", []()
        {
            Vec2 coord;

            AssertThat(coord, Is().EqualTo(Vec2(0.0, 0.0)));
        });

        it("accepts two floats that specify its position", []()
        {
            Vec2 coord(5.0, 6.0);

            AssertThat(coord, Is().EqualTo(Vec2(5.0, 6.0)));
        });

        it("accepts updates to its position", []()
        {
            Vec2 coord(32.0, 126.0);

            AssertThat(coord, Is().EqualTo(Vec2(32.0, 126.0)));

            coord.setX(13.0);
            coord.setY(43.0);

            AssertThat(coord, Is().EqualTo(Vec2(13.0, 43.0)));
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
                AssertThat(negatedVec1, Is().EqualTo(Vec2(-3.f, -4.f)));

                Vec2 someVec2 = Vec2(-4.f, -3.f);
                Vec2 negatedVec2 = -someVec2;
                AssertThat(negatedVec2, Is().EqualTo(Vec2(4.f, 3.f)));
            });
        });

        describe("normalising a Vec2", []()
        {
            it("should result in the Vec2 having a magnitude of 1", []()
            {
                Vec2 someVec1 = Vec2(3.f, 4.f);
                someVec1.normalise();
                AssertThat(someVec1.getMagnitude(), Is().EqualToWithDelta(1.f, FLOAT_EPSILON));
                AssertThat(someVec1, Is().EqualTo(Vec2(0.6f, 0.8f)));

                Vec2 someVec2 = Vec2(-4.f, -3.f);
                someVec2.normalise();
                AssertThat(someVec2.getMagnitude(), Is().EqualToWithDelta(1.f, FLOAT_EPSILON));
                AssertThat(someVec2, Is().EqualTo(Vec2(-0.8f, -0.6f)));
            });
        });

        describe("getting a normalised copy of a Vec2", []()
        {
            it("should result in a new Vec2 with a magnitude of 1", []()
            {
                Vec2 someVec1 = Vec2(3.f, 4.f);
                Vec2 normalised1 = someVec1.getNormalised();
                AssertThat(normalised1.getMagnitude(), Is().EqualToWithDelta(1.f, FLOAT_EPSILON));
                AssertThat(normalised1, Is().EqualTo(Vec2(0.6f, 0.8f)));

                Vec2 someVec2 = Vec2(-4.f, -3.f);
                Vec2 normalised2 = someVec2.getNormalised();
                AssertThat(normalised2.getMagnitude(), Is().EqualToWithDelta(1.f, FLOAT_EPSILON));
                AssertThat(normalised2, Is().EqualTo(Vec2(-0.8f, -0.6f)));
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

                AssertThat(result1, Is().EqualTo(Vec2(88.f, 99.7f)));
                AssertThat(result2, Is().EqualTo(Vec2(-24.f, -1.f)));
                AssertThat(result3, Is().EqualTo(Vec2(-21.3f, 24.7f)));

                origin += target4;

                AssertThat(origin, Is().EqualTo(Vec2(2.f, 1.f)));
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

                AssertThat(offset1, Is().EqualTo(Vec2(-10.f, -12.f)));
                AssertThat(offset2, Is().EqualTo(Vec2(-9.f, 213.f)));
                AssertThat(offset3, Is().EqualTo(Vec2(0.19f, 87.f)));
                AssertThat(offset4, Is().EqualTo(Vec2(1241.f, -3.f)));
                AssertThat(offset5, Is().EqualTo(Vec2(-0.f, -0.f)));
                AssertThat(origin, Is().EqualTo(Vec2(-10.f, -15.f)));
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

                AssertThat(scaled1, Is().EqualTo(Vec2(26.55f, 15.5f)));
                AssertThat(scaled2, Is().EqualTo(Vec2(531.f, 310.f)));
                AssertThat(source, Is().EqualTo(Vec2(53.1f, 31.0f)));
            });

            it("should scale both components of the Vec2 DOWN by the scale factor", [&]()
            {
                Vec2 source = Vec2(5.31f, 3.1f);

                Vec2 scaled3 = source / 10;
                Vec2 scaled4 = source / 2;

                source /= 3;

                AssertThat(scaled3, Is().EqualTo(Vec2(0.531f, 0.31f)));
                AssertThat(scaled4, Is().EqualTo(Vec2(2.655f, 1.55f)));
                AssertThat(source, Is().EqualTo(Vec2(1.77f, 1.033333333f)));
            });
        });
    });
});
