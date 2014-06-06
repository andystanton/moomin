#ifndef _MOOMIN_CIRCLE
#define _MOOMIN_CIRCLE

#include "Entity.hpp"
#include "drawing/Mesh.hpp"

class Circle
    : public Entity
{
public:
    Circle(Vec2 pos, float radius, Vec2 velocity = Vec2::ORIGIN);
    ~Circle();

    float getRadius() const;
    const Mesh & getMesh() const;
private:
    static const int DEFAULT_SEGMENT_COUNT = 36;
    static float * populateMesh(float radius, int segmentCount = DEFAULT_SEGMENT_COUNT);

    float radius;
    Mesh mesh;
};

#endif
