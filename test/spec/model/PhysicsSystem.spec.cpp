#include <bandit/bandit.h>
#include <gmock/gmock.h>

#include "GmockBDDAliases.h"

#include "model/PhysicsSystem.h"
#include "model/rules/AccelerationRule.h"
#include "model/Circle.h"
#include "mock/MockRule.h"
#include "mock/MockEntity.h"

using namespace bandit;

using ::testing::Ref;

go_bandit([]() 
{
    describe("a Physics System", []() 
    {
        it("contains no rules or entities when it is created", []() 
        {
            PhysicsSystem physicsSystem;

            AssertThat(physicsSystem.getEntities(), IsEmpty());
            AssertThat(physicsSystem.getRules(), IsEmpty());
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

            Rule * gravity = new AccelerationRule(Vec2(0.f, -10.f));
            physicsSystem.addRule(gravity);

            AssertThat(physicsSystem.getRules(), HasLength(1));
            AssertThat(physicsSystem.getRules(), Contains(gravity));
        });

        describe("stepping forward", []()
        {
            it("causes the rules to affect the entities", []()
            {
                MockRule rule;
                MockEntity entity;

                PhysicsSystem physicsSystem;

                physicsSystem.addRule(&rule);
                physicsSystem.addEntity(&entity);

                Verify(rule, apply(Ref(entity), 100));

                physicsSystem.step(100);

                //rule.apply(entity, 100);
            });
        });
    });
});