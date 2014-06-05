#include "drawing/Mesh.hpp"


Mesh::Mesh(MeshType type, initializer_list<float> meshComponents)
    : size(meshComponents.size())
    , mesh(new float[meshComponents.size()])
    , type(type)
    , rawMesh()
{
    Vec2* nextVec2 = nullptr;
    //mesh = new float[meshComponents.size()];

    int count = 0;
    for (auto component : meshComponents)
    {
        mesh[count] = component;
        if (nextVec2 == nullptr)
        {
            nextVec2 = new Vec2();
            nextVec2->setX(component);
        } else
        {
            nextVec2->setY(component);
            rawMesh.push_back(nextVec2);
            nextVec2 = nullptr;
        }
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
