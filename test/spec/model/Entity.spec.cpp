#include <bandit/bandit.h>

#include "TestConstants.h"
#include "model/Circle.h"
#include "model/AABB.h"

using namespace bandit;

go_bandit([]()
{
    describe("an Entity", []()
    {
        Entity * e1 = new Circle(Vec2(23.0f, 12.0f), 5.f, Vec2(5.f, 7.f));
        Entity * e2 = new AABB(Vec2(20.f, 20.f), Vec2(5.f, 5.f));

        it("has a position and a velocity", [&]()
        {
            AssertThat(e1->getPos(), Is().EqualTo(Vec2(23.0f, 12.0f)));
            AssertThat(e1->getVelocity(), Is().EqualTo(Vec2(5.f, 7.f)));
            AssertThat(e2->getPos(), Is().EqualTo(Vec2(20.0f, 20.0f)));
            AssertThat(e2->getVelocity(), Is().EqualTo(Vec2(0.f, 0.f)));
        });

        it("has a Collision Type", [&]()
        {
            AssertThat(e1->getCollisionType(), Is().EqualTo(Entity::CollisionType::circle));
            AssertThat(e2->getCollisionType(), Is().EqualTo(Entity::CollisionType::aabb));
        });
    });
});
