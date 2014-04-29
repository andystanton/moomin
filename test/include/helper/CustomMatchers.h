#ifndef _MOOMIN_TEST_CUSTOM_MATCHERS
#define _MOOMIN_TEST_CUSTOM_MATCHERS

#include "model/Entity.h"

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

#endif