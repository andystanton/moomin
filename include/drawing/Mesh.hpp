#ifndef _MOOMIN_MESH
#define _MOOMIN_MESH

#include <initializer_list>
#include <vector>

#include "core/Vec2.hpp"

using std::vector;
using std::initializer_list;

class Mesh
{
public:
    enum class MeshType { quads, triangles, fan };

    Mesh(MeshType, float *, int size);
    Mesh(MeshType, initializer_list<float>);

    Mesh(float *, int size);
    Mesh(initializer_list<float>);

    ~Mesh();

    void setType(MeshType);
    MeshType getType() const;

    float * getPoints() const;
    int getSize() const;
    int getMemSize() const;

    static Mesh empty;
private:
    int size;
    int memSize;
    float * mesh;
    MeshType type;
};

#endif
