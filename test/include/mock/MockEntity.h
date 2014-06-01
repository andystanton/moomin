#ifndef _MOOMIN_MOCK_ENTITY
#define _MOOMIN_MOCK_ENTITY

#include <gmock/gmock.h>

#include "model/Entity.h"
#include "drawing/Mesh.h"

class MockEntity
    : public Entity
{
public:
    MOCK_METHOD0(getPos, const Vec2&());
    MOCK_METHOD0(getVelocity, const Vec2&());

    MOCK_METHOD1(setPos, void(Vec2&));
    MOCK_METHOD1(setVelocity, void(Vec2&));

    MOCK_CONST_METHOD0_T(getMesh, const Mesh&());

    MockEntity()
        : Entity(Vec2(0.f, 0.f), Entity::CollisionType::mock)
    {
    }
};

#endif
