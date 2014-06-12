#include "drawing/Mesh.hpp"

Mesh Mesh::empty = Mesh({}, 0);

Mesh::Mesh(MeshType type, float * components, int size)
    : size(size)
    , memSize(size * sizeof(float))
    , mesh(new float[size])
    , type(type)
{
    for (int i = 0; i < size; i++) { mesh[i] = components[i]; }
}

Mesh::Mesh(MeshType type, initializer_list<float> components)
    : size((int) components.size())
    , memSize(size * sizeof(float))
    , mesh(new float[components.size()])
    , type(type)
{
    int count = 0;
    for (auto component : components)
    {
        mesh[count] = component;
        ++count;
    }
}

Mesh::Mesh(float * components, int size)
    : Mesh(MeshType::triangles, components, size)
{

}

Mesh::Mesh(initializer_list<float> components)
    : Mesh(MeshType::triangles, components)
{

}

Mesh::~Mesh()
{

}

int Mesh::getSize() const
{
    return size;
}

int Mesh::getMemSize() const
{
    return memSize;
}

Mesh::MeshType Mesh::getType() const
{
    return type;
}

float * Mesh::getPoints() const
{
    return mesh;
}
