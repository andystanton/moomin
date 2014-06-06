#include "drawing/Mesh.hpp"


Mesh::Mesh(float * meshComponents, int meshSize)
    : size(meshSize)
    , mesh(new float[meshSize])
{
    for (int i = 0; i < size; i++)
    {
        mesh[i] = meshComponents[i];
    }
}

Mesh::Mesh(MeshType type, initializer_list<float> meshComponents)
    : size(meshComponents.size())
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
