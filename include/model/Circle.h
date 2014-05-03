#ifndef _MOOMIN_CIRCLE
#define _MOOMIN_CIRCLE

#include "Entity.h"
#include "drawing/Mesh.h"

class Circle
    : public Entity
{
public:
    Circle(float x, float y, float radius);
    ~Circle();

    float getRadius();
private:
    float radius;
    Mesh mesh
    {
        0.0f, 0.0f,  0.0f, 10.0f,  1.74f, 9.85f,
        0.0f, 0.0f,  1.74f, 9.85f,  3.42f, 9.4f,
        0.0f, 0.0f,  3.42f, 9.4f,  5.0f, 8.66f,
        0.0f, 0.0f,  5.0f, 8.66f,  6.43f, 7.66f,
        0.0f, 0.0f,  6.43f, 7.66f,  7.66f, 6.43f,
        0.0f, 0.0f,  7.66f, 6.43f,  8.66f, 5.0f,
        0.0f, 0.0f,  8.66f, 5.0f,  9.4f, 3.42f,
        0.0f, 0.0f,  9.4f, 3.42f,  9.85f, 1.74f,
        0.0f, 0.0f,  9.85f, 1.74f,  10.0f, 0.0f,
        0.0f, 0.0f,  10.0f, 0.0f,  9.85f, -1.74f,
        0.0f, 0.0f,  9.85f, -1.74f,  9.4f, -3.42f,
        0.0f, 0.0f,  9.4f, -3.42f,  8.66f, -5.0f,
        0.0f, 0.0f,  8.66f, -5.0f,  7.66f, -6.43f,
        0.0f, 0.0f,  7.66f, -6.43f,  6.43f, -7.66f,
        0.0f, 0.0f,  6.43f, -7.66f,  5.0f, -8.66f,
        0.0f, 0.0f,  5.0f, -8.66f,  3.42f, -9.4f,
        0.0f, 0.0f,  3.42f, -9.4f,  1.74f, -9.85f,
        0.0f, 0.0f,  1.74f, -9.85f,  0.0f, -10.0f,
        0.0f, 0.0f,  0.0f, -10.0f,  -1.74f, -9.85f,
        0.0f, 0.0f,  -1.74f, -9.85f,  -3.42f, -9.4f,
        0.0f, 0.0f,  -3.42f, -9.4f,  -5.0f, -8.66f,
        0.0f, 0.0f,  -5.0f, -8.66f,  -6.43f, -7.66f,
        0.0f, 0.0f,  -6.43f, -7.66f,  -7.66f, -6.43f,
        0.0f, 0.0f,  -7.66f, -6.43f,  -8.66f, -5.0f,
        0.0f, 0.0f,  -8.66f, -5.0f,  -9.4f, -3.42f,
        0.0f, 0.0f,  -9.4f, -3.42f,  -9.85f, -1.74f,
        0.0f, 0.0f,  -9.85f, -1.74f,  -10.0f, 0.0f,
        0.0f, 0.0f,  -10.0f, 0.0f,  -9.85f, 1.74f,
        0.0f, 0.0f,  -9.85f, 1.74f,  -9.4f, 3.42f,
        0.0f, 0.0f,  -9.4f, 3.42f,  -8.66f, 5.0f,
        0.0f, 0.0f,  -8.66f, 5.0f,  -7.66f, 6.43f,
        0.0f, 0.0f,  -7.66f, 6.43f,  -6.43f, 7.66f,
        0.0f, 0.0f,  -6.43f, 7.66f,  -5.0f, 8.66f,
        0.0f, 0.0f,  -5.0f, 8.66f,  -3.42f, 9.4f,
        0.0f, 0.0f,  -3.42f, 9.4f,  -1.74f, 9.85f,
        0.0f, 0.0f,  -1.74f, 9.85f,  0.0f, 10.0f
    };
};

#endif