#include <bandit/bandit.h>

#include "TestConstants.h"
#include "drawing/Mesh.h"

using namespace bandit;

go_bandit([]()
{
    describe("a Mesh", []()
    {
        it("has a default mesh type of triangles by default", []()
        {
            Mesh mesh({});

            AssertThat(mesh.getType(), Is().EqualTo(Mesh::MeshType::triangles));
        });

        it("accepts an initializer_list of floats that specify its coordinates", []()
        {
            Mesh mesh
            {
                0.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 1.0f
            };

            AssertThat(mesh.getSize(), Is().EqualToWithDelta(6, FLOAT_EPSILON));

            float * meshPoints = mesh.getPoints();

            AssertThat(meshPoints[0], Is().EqualToWithDelta(0.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[1], Is().EqualToWithDelta(0.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[2], Is().EqualToWithDelta(0.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[3], Is().EqualToWithDelta(1.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[4], Is().EqualToWithDelta(1.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[5], Is().EqualToWithDelta(1.0f, FLOAT_EPSILON));
        });

        it("accepts a mesh type and an initializer_list of floats that specify its coordinates", []()
        {
            Mesh mesh = Mesh(
                Mesh::MeshType::quads,
                {
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f
                }
            );

            AssertThat(mesh.getSize(), Is().EqualToWithDelta(8, FLOAT_EPSILON));

            float * meshPoints = mesh.getPoints();

            AssertThat(meshPoints[0], Is().EqualToWithDelta(0.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[1], Is().EqualToWithDelta(0.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[2], Is().EqualToWithDelta(0.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[3], Is().EqualToWithDelta(1.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[4], Is().EqualToWithDelta(1.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[5], Is().EqualToWithDelta(1.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[6], Is().EqualToWithDelta(1.0f, FLOAT_EPSILON));
            AssertThat(meshPoints[7], Is().EqualToWithDelta(0.0f, FLOAT_EPSILON));
        });

        it("accepts updates to its mesh type", []()
        {
            Mesh mesh({});

            AssertThat(mesh.getType(), Is().EqualTo(Mesh::MeshType::triangles));

            mesh.setType(Mesh::MeshType::quads);

            AssertThat(mesh.getType(), Is().EqualTo(Mesh::MeshType::quads));
        });
    });
});
