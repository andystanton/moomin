#include "model/Entity.h"

Entity::Entity(const Mesh& mesh)
    : mesh(mesh) 
{

}

Entity::~Entity() 
{

}

const Mesh& Entity::getMesh() 
{
    return mesh;
}