#include <bandit/bandit.h>

#include "model/PhysicsSystem.h"
#include "model/rules/AccelerationRule.h"
#include "model/Circle.h"

using namespace bandit;

go_bandit([]() 
{
    describe("a Physics System", []() 
    {
        it("contains no entities when it is created", []() 
        {
            PhysicsSystem physicsSystem;

            AssertThat(physicsSystem.getEntities().size(), Is().EqualTo(0));
        });

        it("allows entities to be created within it", []()
        {
            PhysicsSystem physicsSystem;

            AssertThat(physicsSystem.getEntities(), IsEmpty());

            Circle someCircle = Circle(100.f, 100.f, 10.f);
            physicsSystem.addEntity(&someCircle);

            AssertThat(physicsSystem.getEntities(), HasLength(1));
            AssertThat(physicsSystem.getEntities(), Contains(&someCircle));
        });

        it("allows rules to be created within it", []()
        {
            PhysicsSystem physicsSystem;

            AssertThat(physicsSystem.getRules(), IsEmpty());

            Rule gravity = AccelerationRule(Vec2(0.f, -10.f));
            physicsSystem.addRule(&gravity);

            AssertThat(physicsSystem.getRules(), HasLength(1));
            AssertThat(physicsSystem.getRules(), Contains(&gravity));

        });
    });
});
