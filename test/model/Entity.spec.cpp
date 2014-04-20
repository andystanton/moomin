#include <bandit/bandit.h>

#include "model/Entity.h"
#include "drawing/Mesh.h"

using namespace bandit;
using namespace std;

go_bandit([]() 
{
    describe("an Entity", []() 
    {
        it("accepts a position and mesh", []() 
        {
            Mesh mesh 
            {
                0.0, 0.0,
                0.0, 1.0,
                1.0, 1.0,
                1.0, 0.0
            };
            mesh.setType(Mesh::MeshType::quads);

            Entity entity(23.0, 12.0, mesh);

            AssertThat(entity.getPos().getX(), Is().EqualTo(23.0));
            AssertThat(entity.getPos().getY(), Is().EqualTo(12.0));

            AssertThat(&entity.getMesh(), Is().EqualTo(&mesh));
        });
    });
});
