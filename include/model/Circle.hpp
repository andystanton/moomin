#ifndef _MOOMIN_CIRCLE
#define _MOOMIN_CIRCLE

#include "Entity.hpp"
#include "drawing/Mesh.hpp"

class Circle
    : public Entity
{
public:
    Circle(Vec2 pos, float radius, Vec2 velocity = Vec2(0.f, 0.f));
    ~Circle();

    float getRadius();
    const Mesh & getMesh() const;
private:
    float radius;
    Mesh mesh;

    static const int SEGMENT_COUNT = 36;
    static float * populateMesh(float radius)
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
};

#endif
