#include "model/Circle.hpp"

Circle::Circle(Vec2 pos, float radius, Vec2 velocity)
    : Entity(pos, Entity::CollisionType::circle, populateMesh(radius), velocity)
    , radius(radius)
{

}

Circle::~Circle()
{

}

float Circle::getRadius() const
{
    return radius;
}

Mesh Circle::populateMesh(float radius, int segmentCount)
{
    int size = (segmentCount + 1) * 2 + 2 + 2;

    float * meshComponents = new float[size];

    float segmentAngle = 360 / segmentCount;

    meshComponents[0] = 0.f;
    meshComponents[1] = 0.f;

    int offset = 3;
    for (int count = -1; count < segmentCount; count++, offset++)
    {
        float angle = count * segmentAngle;

        meshComponents[count + offset] = sin(angle * M_PI / 180) * radius;
        meshComponents[count + offset + 1] = cos(angle * M_PI / 180) * radius;
    }

    meshComponents[size - 2] = 0.f;
    meshComponents[size - 1] = 0.f;

    return Mesh(Mesh::MeshType::fan, meshComponents, (DEFAULT_SEGMENT_COUNT + 1) * 2 + 2 + 2);
}
