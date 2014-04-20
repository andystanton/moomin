#include <bandit/bandit.h>

#include "drawing/Mesh.h"

using namespace bandit; 

go_bandit([]() {
    describe("a Mesh", []() {
        describe("Mesh()", []() {
            it("has a default Mesh Type of Triangles by default", [&]() {
                Mesh mesh {};
                AssertThat(mesh.getType(), Is().EqualTo(Mesh::MeshType::tris));
            });

            it("accepts an initializer_list of floats as its argument", [&]() {
                Mesh mesh {
                    0.0, 0.0,
                    0.0, 1.0,
                    1.0, 1.0
                };
                float * meshPoints = mesh.getPoints();
                AssertThat(meshPoints[0], Is().EqualTo(0.0));
                AssertThat(meshPoints[1], Is().EqualTo(0.0));
                AssertThat(meshPoints[2], Is().EqualTo(0.0));
                AssertThat(meshPoints[3], Is().EqualTo(1.0));
                AssertThat(meshPoints[4], Is().EqualTo(1.0));
                AssertThat(meshPoints[5], Is().EqualTo(1.0));
            });
        });
    });
});
