#include <bandit/bandit.h>

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

            AssertThat(mesh.getSize(), Is().EqualTo(6));

            float * meshPoints = mesh.getPoints();

            AssertThat(meshPoints[0], Is().EqualTo(0.0f));
            AssertThat(meshPoints[1], Is().EqualTo(0.0f));
            AssertThat(meshPoints[2], Is().EqualTo(0.0f));
            AssertThat(meshPoints[3], Is().EqualTo(1.0f));
            AssertThat(meshPoints[4], Is().EqualTo(1.0f));
            AssertThat(meshPoints[5], Is().EqualTo(1.0f));
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

            AssertThat(mesh.getSize(), Is().EqualTo(8));

            float * meshPoints = mesh.getPoints();

            AssertThat(meshPoints[0], Is().EqualTo(0.0f));
            AssertThat(meshPoints[1], Is().EqualTo(0.0f));
            AssertThat(meshPoints[2], Is().EqualTo(0.0f));
            AssertThat(meshPoints[3], Is().EqualTo(1.0f));
            AssertThat(meshPoints[4], Is().EqualTo(1.0f));
            AssertThat(meshPoints[5], Is().EqualTo(1.0f));
            AssertThat(meshPoints[6], Is().EqualTo(1.0f));
            AssertThat(meshPoints[7], Is().EqualTo(0.0f));
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
