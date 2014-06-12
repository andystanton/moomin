#include "model/Circle.hpp"

const int Circle::DEFAULT_SEGMENT_COUNT = 36;

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

float * Circle::getColour()
{
    return new float[4] { 0.4f, 0.8f, 0.4f, 0.f };
}

Mesh Circle::populateMesh(float radius, int segmentCount)
{
    // number of components is equal to the number of segments + 1 because
    // triangle fans require reiterating the second vertex. The extra 4
    // are required as we have to hit the origin twice - once at the start
    // and once at the end.
    int componentCount = (segmentCount + 1) * 2 + 4;

    float * meshComponents = new float[componentCount];

    float segmentAngle = 360 / segmentCount;

    meshComponents[0] = 0.f;
    meshComponents[1] = 0.f;

    int indexOffset = 2; // offset as we've manually set 0 and 1.

    for (int count = 0; count <= segmentCount; count++, indexOffset++)
    {
        float angle = count * segmentAngle;

        meshComponents[count + indexOffset]     = sin(angle * M_PI / 180) * radius;
        meshComponents[count + indexOffset + 1] = cos(angle * M_PI / 180) * radius;
    }

    meshComponents[componentCount - 2] = 0.f;
    meshComponents[componentCount - 1] = 0.f;

    return Mesh(Mesh::MeshType::fan, meshComponents, componentCount);
}
