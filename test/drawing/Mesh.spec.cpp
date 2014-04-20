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

            AssertThat(mesh.getType(), Is().EqualTo(Mesh::MeshType::tris));
        });

        it("accepts an initializer_list of floats that specify its coordinates", []() 
        {
            Mesh mesh 
            {
                0.0, 0.0,
                0.0, 1.0,
                1.0, 1.0
            };

            AssertThat(mesh.getSize(), Is().EqualTo(6));

            float * meshPoints = mesh.getPoints();

            AssertThat(meshPoints[0], Is().EqualTo(0.0));
            AssertThat(meshPoints[1], Is().EqualTo(0.0));
            AssertThat(meshPoints[2], Is().EqualTo(0.0));
            AssertThat(meshPoints[3], Is().EqualTo(1.0));
            AssertThat(meshPoints[4], Is().EqualTo(1.0));
            AssertThat(meshPoints[5], Is().EqualTo(1.0));
        });

        it("accepts updates to its mesh type", []() 
        {
            Mesh mesh({});

            AssertThat(mesh.getType(), Is().EqualTo(Mesh::MeshType::tris));

            mesh.setType(Mesh::MeshType::quads);
            
            AssertThat(mesh.getType(), Is().EqualTo(Mesh::MeshType::quads));
        });
    });
});
