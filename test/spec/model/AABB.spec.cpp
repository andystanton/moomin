#include <bandit/bandit.h>

#include "TestConstants.hpp"
#include "core/Core.hpp"
#include "model/AABB.hpp"
#include "drawing/Mesh.hpp"

using namespace bandit;

go_bandit([]()
{
    describe("an Axis-Aligned Bounding Box", []()
    {
        it("is a subclass of Entity", []()
        {
            Entity * aabb = new AABB(Vec2(50.f, 50.f), Vec2(10.f, 10.f));

            AssertThat(aabb->getPos(), Is().EqualTo(Vec2(50.f, 50.f)));
        });

        it("accepts a position and dimensions", []()
        {
            AABB aabb(Vec2(50.f, 50.f), Vec2(10.f, 10.f));

            AssertThat(aabb.getPos(), Is().EqualTo(Vec2(50.f, 50.f)));
            AssertThat(aabb.getBounding(), Is().EqualTo(Vec2(10.f, 10.f)));
        });

        it("has a Mesh defined by its Bounding coordinates", []()
        {
            AABB aabb(Vec2(50.f, 50.f), Vec2(40.f, 60.f));

            float * points = aabb.getMesh().getPoints();

            AssertThat(aabb.getMesh().getType(), Is().EqualTo(Mesh::MeshType::triangles));

            AssertThat(points[0], Is().EqualToWithDelta(0.f, FLOAT_EPSILON));
            AssertThat(points[1], Is().EqualToWithDelta(0.f, FLOAT_EPSILON));

            AssertThat(points[2], Is().EqualToWithDelta(0.f, FLOAT_EPSILON));
            AssertThat(points[3], Is().EqualToWithDelta(60.f, FLOAT_EPSILON));

            AssertThat(points[4], Is().EqualToWithDelta(40.f, FLOAT_EPSILON));
            AssertThat(points[5], Is().EqualToWithDelta(60.f, FLOAT_EPSILON));

            AssertThat(points[6], Is().EqualToWithDelta(0.f, FLOAT_EPSILON));
            AssertThat(points[7], Is().EqualToWithDelta(0.f, FLOAT_EPSILON));

            AssertThat(points[8], Is().EqualToWithDelta(40.f, FLOAT_EPSILON));
            AssertThat(points[9], Is().EqualToWithDelta(60.f, FLOAT_EPSILON));

            AssertThat(points[10], Is().EqualToWithDelta(40.f, FLOAT_EPSILON));
            AssertThat(points[11], Is().EqualToWithDelta(0.f, FLOAT_EPSILON));
        });
    });
});
