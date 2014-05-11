#include <bandit/bandit.h>

#include "core/Core.h"
#include "model/AABB.h"
#include "drawing/Mesh.h"

#include <iostream>

using namespace std;

using namespace bandit;

go_bandit([]() 
{
    describe("an Axis-Aligned Bounding Box", []() 
    {
        it("is a subclass of Entity", []() 
        {
            Entity * aabb = new AABB(50.f, 50.f, 10.f, 10.f);

            AssertThat(aabb->getPos().getX(), Is().EqualTo(50.f));
            AssertThat(aabb->getPos().getY(), Is().EqualTo(50.f));
        });

        it("accepts a position and a radius", []()
        {
            AABB aabb(50.f, 50.f, 10.f, 10.f);

            AssertThat(aabb.getPos().getX(), Is().EqualTo(50.f));
            AssertThat(aabb.getPos().getY(), Is().EqualTo(50.f));

            AssertThat(aabb.getBounding().getX(), Is().EqualTo(10.f));
            AssertThat(aabb.getBounding().getY(), Is().EqualTo(10.f));
        });

        it("has a Mesh defined by its Bounding coordinates", []()
        {
            AABB aabb(50.f, 50.f, 40.f, 60.f);

            float * points = aabb.getMesh().getPoints();

            AssertThat(aabb.getMesh().getType(), Is().EqualTo(Mesh::MeshType::quads));

            AssertThat(points[0], Is().EqualTo(0.f));
            AssertThat(points[1], Is().EqualTo(0.f));

            AssertThat(points[2], Is().EqualTo(0.f));
            AssertThat(points[3], Is().EqualTo(60.f));

            AssertThat(points[4], Is().EqualTo(40.f));
            AssertThat(points[5], Is().EqualTo(0.f));

            AssertThat(points[6], Is().EqualTo(40.f));
            AssertThat(points[7], Is().EqualTo(60.f));
        });
    });
});
