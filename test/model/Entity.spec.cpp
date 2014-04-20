#include <bandit/bandit.h>

#include "model/Entity.h"
#include "drawing/Mesh.h"

using namespace bandit;
using namespace std;

go_bandit([]() 
{
    describe("an Entity", []() 
    {
        it("has a mesh", []() 
        {
            Mesh mesh 
            {
                0.0, 0.0,
                0.0, 1.0,
                1.0, 1.0,
                1.0, 0.0
            };
            mesh.setType(Mesh::MeshType::quads);

            Entity entity(mesh);

            AssertThat(&mesh, Is().EqualTo(&entity.getMesh()));
        });
    });
});
