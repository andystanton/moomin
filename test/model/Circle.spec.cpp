#include <bandit/bandit.h>

#include "core/Core.h"
#include "model/Circle.h"
#include "drawing/Mesh.h"

using namespace bandit;

struct IsInstanceOfEntity
{
  bool Matches(const Entity * actual) const
  {
    return actual != nullptr; 
  }

  friend std::ostream& operator<<(std::ostream& stm, const IsInstanceOfEntity& );
};

std::ostream& operator<<(std::ostream& stm, const IsInstanceOfEntity& )
{
  stm << "Not Null";
  return stm;
}

go_bandit([]() 
{
    describe("a Circle", []() 
    {
        it("is a subclass of Entity", []() 
        {
            Circle * circle = new Circle(50.f, 100.f, 10.f);

            AssertThat(dynamic_cast<Entity *>(circle), Fulfills(IsInstanceOfEntity()));
        });

        it("accepts a position and a radius", []()
        {
            Circle circle = Circle(50.4f, 100.f, 10.f);

            AssertThat(circle.getPos().getX(), Is().EqualTo(50.4f));
            AssertThat(circle.getPos().getY(), Is().EqualTo(100.f));
            AssertThat(circle.getRadius(), Is().EqualTo(10.f));
        });
    });
});
