#include "model/Circle.hpp"

Circle::Circle(Vec2 pos, float radius, Vec2 velocity)
    : Entity(pos, Entity::CollisionType::circle, velocity)
    , radius(radius)
    , mesh(populateMesh(radius), (SEGMENT_COUNT + 1) * 2 + 2 + 2)
{
    mesh.setType(Mesh::MeshType::fan);
}

Circle::~Circle()
{

}

float Circle::getRadius() const
{
    return radius;
}

const Mesh & Circle::getMesh() const
{
    return mesh;
}

float * Circle::populateMesh(float radius)
{
    int size = (SEGMENT_COUNT + 1) * 2 + 2 + 2;

    float * meshComponents = new float[size];

    float segmentAngle = 360 / SEGMENT_COUNT;

    meshComponents[0] = 0.f;
    meshComponents[1] = 0.f;

    int offset = 3;
    for (int count = -1; count < SEGMENT_COUNT; count++, offset++)
    {
        float angle = count * segmentAngle;

        meshComponents[count + offset] = sin(angle * M_PI / 180) * radius;
        meshComponents[count + offset + 1] = cos(angle * M_PI / 180) * radius;
    }

    meshComponents[size - 2] = 0.f;
    meshComponents[size - 1] = 0.f;

    return meshComponents;
}
