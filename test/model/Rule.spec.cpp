#include <bandit/bandit.h>

#include "model/Rule.h"
#include "model/rules/AccelerationRule.h"
#include "core/Vec2.h"

using namespace bandit;

struct IsInstanceOfRule
{
  bool Matches(const Rule * actual) const
  {
    return actual != nullptr; 
  }

  friend std::ostream& operator<<(std::ostream& stm, const IsInstanceOfRule& );
};

std::ostream& operator<<(std::ostream& stm, const IsInstanceOfRule& )
{
  stm << "Not Null";
  return stm;
}

go_bandit([]() 
{
    describe("the Rules", []() 
    {
        describe("an Acceleration Rule", []()
        {
            it("is an instance of a Rule", []()
            {
                AccelerationRule * gravity = new AccelerationRule(Vec2(0.f, 10.f));
                AssertThat(dynamic_cast<Rule *>(gravity), Fulfills(IsInstanceOfRule()));
            });

            it("accepts a Vec2 as its argument", []() 
            {
                AccelerationRule gravity(Vec2(0.f, 10.f));

                AssertThat(gravity.getAcceleration().getX(), Is().EqualTo(0.f));
                AssertThat(gravity.getAcceleration().getY(), Is().EqualTo(10.f));
            });
        });
    });
});
