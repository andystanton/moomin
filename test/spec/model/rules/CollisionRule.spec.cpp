#include <bandit/bandit.h>

#include "model/Rule.h"
#include "model/rules/CollisionRule.h"
#include "model/Circle.h"
#include "core/Vec2.h"

#include "mock/MockEntity.h"

using namespace bandit;

go_bandit([]() 
{
    describe("a Collision Rule", []()
    {
        it("is an instance of a Rule", [&]()
        {
            CollisionRule circleCollision;
            Rule * circleCollisionAsRule = &circleCollision;

            MockEntity entity;
            circleCollisionAsRule->apply(entity, 100.f);
        });
    });
});
