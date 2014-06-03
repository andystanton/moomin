#ifndef _MOOMIN_MOCK_VEC2
#define _MOOMIN_MOCK_VEC2

#include <gmock/gmock.h>
#include "core/Vec2.hpp"

class MockVec2
    : public Vec2
{
public:
    MOCK_METHOD0(getX, float());
    MOCK_METHOD0(getY, float());
};

#endif
