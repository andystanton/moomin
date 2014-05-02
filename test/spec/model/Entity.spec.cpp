#include <bandit/bandit.h>

#include "model/Entity.h"
#include "drawing/Mesh.h"

using namespace bandit;

go_bandit([]() 
{
    describe("an Entity", []() 
    {
        it("accepts a position and mesh", []() 
        {
            Mesh mesh 
            {
                0.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f
            };
            mesh.setType(Mesh::MeshType::quads);

            Entity entity(23.0f, 12.0f, mesh);

            AssertThat(entity.getPos().getX(), Is().EqualTo(23.0f));
            AssertThat(entity.getPos().getY(), Is().EqualTo(12.0f));

            AssertThat(&entity.getMesh(), Is().EqualTo(&mesh));
        });
    });
});
