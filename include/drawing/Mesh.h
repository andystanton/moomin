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
    enum class MeshType { quads, triangles, fan };

    Mesh(initializer_list<float>);
    Mesh(MeshType, initializer_list<float>);
    ~Mesh();

    void setType(MeshType);
    MeshType getType() const;
    float * getPoints() const;
    int getSize() const;
private:
    int size;
    MeshType type;
    vector<Vec2*> mesh;
};

#endif
