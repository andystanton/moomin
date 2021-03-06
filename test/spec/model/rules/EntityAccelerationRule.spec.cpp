#include <bandit/bandit.h>

#include "TestConstants.hpp"
#include "model/Rule.hpp"
#include "model/rules/EntityAccelerationRule.hpp"
#include "model/Circle.hpp"
#include "mock/MockEntity.hpp"
#include "core/Vec2.hpp"

#include <set>

using namespace bandit;
using std::set;

go_bandit([]()
{
    describe("an Entity Acceleration Rule", []()
    {
        it("is an instance of a Rule", []()
        {
            set<Entity *> entities;
            entities.insert(new Circle(Vec2(0.f, 0.f), 10.f));
            entities.insert(new Circle(Vec2(100.f, 0.f), 10.f));

            Rule * gravityField = new EntityAccelerationRule(entities, 10.f);

            MockEntity entity;
            gravityField->apply(entity, 100.f);
        });

        it("accepts a set of Entities to apply acceleration too and an acceleration in units/second^2", []()
        {
            set<Entity *> entities;
            entities.insert(new Circle(Vec2(0.f, 0.f), 10.f));
            entities.insert(new Circle(Vec2(100.f, 0.f), 10.f));

            EntityAccelerationRule gravityField(entities, 10.f);

            AssertThat(gravityField.getEntities(), HasLength(2));
            AssertThat(gravityField.getAcceleration(), Is().EqualToWithDelta(10.f, FLOAT_EPSILON));
        });

        it("applies its acceleration to the set of Entities given a time delta in ms toward the target Entity", []()
        {
            Circle circle1(Vec2(0.f, 0.f),   10.f);
            Circle circle2(Vec2(400.f, 300.f),   10.f);

            set<Entity *> entities;
            entities.insert(&circle1);
            entities.insert(&circle2);

            // set gravityField acceleration to 10 units/second^2 toward other Entities
            EntityAccelerationRule gravityField(entities, 10.f);

            // assert that both circles have zero velocity at the start
            AssertThat(circle1.getVelocity(), Is().EqualTo(Vec2(0.f, 0.f)));
            AssertThat(circle2.getVelocity(), Is().EqualTo(Vec2(0.f, 0.f)));

            float timeDeltaSeconds = 0.1;

            // after 100ms, assert the expected change in velocity
            gravityField.apply(circle1, timeDeltaSeconds);
            gravityField.apply(circle2, timeDeltaSeconds);

            AssertThat(circle1.getVelocity(), Is().EqualTo(Vec2( 0.8f,  0.6f)));
            AssertThat(circle2.getVelocity(), Is().EqualTo(Vec2(-0.8f, -0.6f)));

            // after another 100ms, assert the expected change in velocity
            gravityField.apply(circle1, timeDeltaSeconds);
            gravityField.apply(circle2, timeDeltaSeconds);

            AssertThat(circle1.getVelocity(), Is().EqualTo(Vec2( 1.6f,  1.2f)));
            AssertThat(circle2.getVelocity(), Is().EqualTo(Vec2(-1.6f, -1.2f)));
        });

        it("can be inverted", []()
        {
            Circle circle1(Vec2(0.f, 0.f),   10.f);
            Circle circle2(Vec2(400.f, 300.f),   10.f);

            set<Entity *> entities;
            entities.insert(&circle1);
            entities.insert(&circle2);

            // set gravityField acceleration to 10 units/second^2 toward other Entities
            EntityAccelerationRule gravityField(entities, 10.f);

            // then invert it
            gravityField.setInverted(true);

            // assert that both circles have zero velocity at the start
            AssertThat(circle1.getVelocity(), Is().EqualTo(Vec2(0.f, 0.f)));
            AssertThat(circle2.getVelocity(), Is().EqualTo(Vec2(0.f, 0.f)));

            float timeDeltaSeconds = 0.1;

            // after 100ms, assert the expected change in velocity
            gravityField.apply(circle1, timeDeltaSeconds);
            gravityField.apply(circle2, timeDeltaSeconds);

            AssertThat(circle1.getVelocity(), Is().EqualTo(Vec2(-0.8f, -0.6f)));
            AssertThat(circle2.getVelocity(), Is().EqualTo(Vec2( 0.8f,  0.6f)));

            // after another 100ms, assert the expected change in velocity
            gravityField.apply(circle1, timeDeltaSeconds);
            gravityField.apply(circle2, timeDeltaSeconds);

            AssertThat(circle1.getVelocity(), Is().EqualTo(Vec2(-1.6f, -1.2f)));
            AssertThat(circle2.getVelocity(), Is().EqualTo(Vec2( 1.6f,  1.2f)));
        });
    });
});
