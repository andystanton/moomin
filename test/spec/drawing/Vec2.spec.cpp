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
});
