#ifndef _MOOMIN_MESH
#define _MOOMIN_MESH

#include <initializer_list>
#include <vector>

#include "core/Vec2.h"

using std::vector;
using std::initializer_list;

class Mesh
{
public:
    enum class MeshType { quads, tris };

    Mesh(initializer_list<float>);
    ~Mesh();

    MeshType getType();
    float * getPoints();
private:
    vector<Vec2*> mesh;
    MeshType type = MeshType::tris;
};

#endif
