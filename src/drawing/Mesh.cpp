#include "drawing/Mesh.h"

Mesh::Mesh(initializer_list<float> meshComponents)
    : mesh {}
    , size(0)
    , type(MeshType::tris) 
{
    Vec2* nextVec2 = nullptr;
    for (auto component : meshComponents) 
    {
        if (nextVec2 == nullptr) 
        {
            nextVec2 = new Vec2();
            nextVec2->setX(component);
        } else 
        {
            nextVec2->setY(component);
            mesh.push_back(nextVec2);
            nextVec2 = nullptr;
        }
        ++size;
    }
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
    float * points = new float[mesh.size() * 2];
    int i = 0;

    for (auto vec2 : mesh) 
    {
        points[i++] = vec2->getX();
        points[i++] = vec2->getY();
    }
    return points;
}
