#include <bandit/bandit.h>

#include "model/Rule.h"
#include "model/rules/EntityAccelerationRule.h"
#include "model/Circle.h"
#include "core/Vec2.h"

#include <set>

#include "mock/MockEntity.h"

using namespace bandit;

using std::set;

go_bandit([]() 
{
    describe("an Entity Acceleration Rule", []()
    {
        it("is an instance of a Rule", []()
        {
            set<Entity *> entities;
            entities.insert(new Circle(0.f, 0.f, 10.f));
            entities.insert(new Circle(100.f, 0.f, 10.f));

            Rule * gravityField = new EntityAccelerationRule(entities);
            
            MockEntity entity;
            gravityField->apply(entity, 100.f);
        });

        it("accepts a set of Entities to apply acceleration too", []() 
        {
            set<Entity *> entities;
            entities.insert(new Circle(0.f, 0.f, 10.f));
            entities.insert(new Circle(100.f, 0.f, 10.f));

            EntityAccelerationRule gravityField(entities);

            AssertThat(gravityField.getEntities(), HasLength(2));
        });
    });
});
