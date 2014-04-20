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
    void setType(MeshType);
    float * getPoints();
    int getSize();
private:
    int size;
    MeshType type;
    vector<Vec2*> mesh;
};

#endif
