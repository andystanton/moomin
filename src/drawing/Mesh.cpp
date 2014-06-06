#include "drawing/Mesh.hpp"

Mesh Mesh::empty = Mesh({}, 0);

Mesh::Mesh(MeshType type, float * components, int meshSize)
    : size(meshSize)
    , memSize(size * sizeof(float))
    , mesh(new float[meshSize])
    , type(type)
{
    for (int i = 0; i < size; i++)
    {
        mesh[i] = components[i];
    }
}

Mesh::Mesh(MeshType type, initializer_list<float> components)
    : size(components.size())
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

Mesh::Mesh(float * components, int meshSize)
    : Mesh(MeshType::triangles, components, meshSize)
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

void Mesh::setType(Mesh::MeshType type)
{
    this->type = type;
}

float * Mesh::getPoints() const
{
    return mesh;
}
