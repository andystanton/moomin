#include "drawing/Mesh.hpp"

Mesh::Mesh(MeshType type, float * meshComponents, int meshSize)
    : size(meshSize)
    , memSize(size * sizeof(float))
    , mesh(new float[meshSize])
    , type(type)
{
    for (int i = 0; i < size; i++)
    {
        mesh[i] = meshComponents[i];
    }
}

Mesh::Mesh(float * meshComponents, int meshSize)
    : Mesh(MeshType::triangles, meshComponents, meshSize)
{
}

Mesh::Mesh(MeshType type, initializer_list<float> meshComponents)
    : size(meshComponents.size())
    , memSize(size * sizeof(float))
    , mesh(new float[meshComponents.size()])
    , type(type)
{
    int count = 0;
    for (auto component : meshComponents)
    {
        mesh[count] = component;
        ++count;
    }
}

Mesh::Mesh(initializer_list<float> meshComponents)
    : Mesh(MeshType::triangles, meshComponents)
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
