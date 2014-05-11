#include <bandit/bandit.h>

#include "model/Circle.h"
#include "model/AABB.h"

using namespace bandit;

go_bandit([]() 
{
    describe("an Entity", []() 
    {
        Entity * e1 = new Circle(23.0f, 12.0f, 5.f);
        Entity * e2 = new AABB(20.f, 20.f, 5.f, 5.f);

        e1->getVelocity().setX(5.f);
        e1->getVelocity().setY(7.f);

        it("has a position and a velocity", [&]() 
        {
            AssertThat(e1->getPos().getX(), Is().EqualTo(23.0f));
            AssertThat(e1->getPos().getY(), Is().EqualTo(12.0f));

            AssertThat(e1->getVelocity().getX(), Is().EqualTo(5.f));
            AssertThat(e1->getVelocity().getY(), Is().EqualTo(7.f));

            AssertThat(e2->getPos().getX(), Is().EqualTo(20.0f));
            AssertThat(e2->getPos().getY(), Is().EqualTo(20.0f));

            AssertThat(e2->getVelocity().getX(), Is().EqualTo(0.f));
            AssertThat(e2->getVelocity().getY(), Is().EqualTo(0.f));
        });

        it("has a Collision Type", [&]()
        {
            AssertThat(e1->getCollisionType(), Is().EqualTo(Entity::CollisionType::circle));
            AssertThat(e2->getCollisionType(), Is().EqualTo(Entity::CollisionType::aabb));
        });
    });
});
