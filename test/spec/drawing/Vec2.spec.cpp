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

        describe("adding two Vec2 together", []()
        {
            it("should give the sum of the Vec2", []()
            {
                Vec2 origin = Vec2(-12.f, -0.3f);

                Vec2 target1 = Vec2(100.f, 100.f);
                Vec2 target2 = Vec2(-12.f, -0.7f);
                Vec2 target3 = Vec2(-9.3f, 25.f);

                unique_ptr<Vec2> result1 = origin.add(target1);
                unique_ptr<Vec2> result2 = origin.add(target2);
                unique_ptr<Vec2> result3 = origin.add(target3);

                AssertThat(result1->getX(), Is().EqualTo(88.f));
                AssertThat(result1->getY(), Is().EqualTo(99.7f));

                AssertThat(result2->getX(), Is().EqualTo(-24.f));
                AssertThat(result2->getY(), Is().EqualTo(-1.f));

                AssertThat(result3->getX(), Is().EqualTo(-21.3f));
                AssertThat(result3->getY(), Is().EqualTo(24.7f));
            });
        });

        describe("subtracting one Vec2 from another", []()
        {
            it("should give the position of the second relative to the first", []()
            {
                Vec2 origin = Vec2(0.f, 0.f);

                Vec2 target1 = Vec2(10.f, 12.f);
                Vec2 target2 = Vec2(9.f, -213.f);
                Vec2 target3 = Vec2(-0.19f, -87.f);
                Vec2 target4 = Vec2(-1241.f, 3.f);
                Vec2 target5 = Vec2(0.f, 0.f);

                unique_ptr<Vec2> offset1 = origin.subtract(target1);
                unique_ptr<Vec2> offset2 = origin.subtract(target2);
                unique_ptr<Vec2> offset3 = origin.subtract(target3);
                unique_ptr<Vec2> offset4 = origin.subtract(target4);
                unique_ptr<Vec2> offset5 = origin.subtract(target5);

                AssertThat(offset1->getX(), Is().EqualTo(-10.f));
                AssertThat(offset1->getY(), Is().EqualTo(-12.f));

                AssertThat(offset2->getX(), Is().EqualTo(-9.f));
                AssertThat(offset2->getY(), Is().EqualTo(213.f));

                AssertThat(offset3->getX(), Is().EqualTo(0.19f));
                AssertThat(offset3->getY(), Is().EqualTo(87.f));

                AssertThat(offset4->getX(), Is().EqualTo(1241.f));
                AssertThat(offset4->getY(), Is().EqualTo(-3.f));

                AssertThat(offset5->getX(), Is().EqualTo(-0.f));
                AssertThat(offset5->getY(), Is().EqualTo(-0.f));
            });
        });
    });
});
