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
    static const int numSegments = 36;

    float radius;
    Mesh mesh;

    static float * populateMesh(float radius)
    {
        int size = (numSegments + 1) * 2 + 2 + 2;

        float * points = new float[size];

        float segmentAngle = 360 / numSegments;

        points[0] = 0.f;
        points[1] = 0.f;

        int j = 3;
        for (int i = -1; i < numSegments; i++, j++)
        {
            float angle = i * segmentAngle;

            points[i + j] = sin(angle * M_PI / 180) * radius;
            points[i + j + 1] = cos(angle * M_PI / 180) * radius;
        }

        points[size - 2] = 0.f;
        points[size - 1] = 0.f;

        return points;
    }
};

#endif
