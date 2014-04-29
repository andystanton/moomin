#ifndef _MOOMIN_CIRCLE
#define _MOOMIN_CIRCLE

#include "Entity.h"
#include "drawing/Mesh.h"

class Circle
    : public Entity
{
public:
    Circle(float x, float y);
    ~Circle();
private:
    Mesh mesh
    {
        0.0, 0.0,  0.0, 10.0,  1.74, 9.85,
        0.0, 0.0,  1.74, 9.85,  3.42, 9.4,
        0.0, 0.0,  3.42, 9.4,  5.0, 8.66,
        0.0, 0.0,  5.0, 8.66,  6.43, 7.66,
        0.0, 0.0,  6.43, 7.66,  7.66, 6.43,
        0.0, 0.0,  7.66, 6.43,  8.66, 5.0,
        0.0, 0.0,  8.66, 5.0,  9.4, 3.42,
        0.0, 0.0,  9.4, 3.42,  9.85, 1.74,
        0.0, 0.0,  9.85, 1.74,  10.0, 0.0,
        0.0, 0.0,  10.0, 0.0,  9.85, -1.74,
        0.0, 0.0,  9.85, -1.74,  9.4, -3.42,
        0.0, 0.0,  9.4, -3.42,  8.66, -5.0,
        0.0, 0.0,  8.66, -5.0,  7.66, -6.43,
        0.0, 0.0,  7.66, -6.43,  6.43, -7.66,
        0.0, 0.0,  6.43, -7.66,  5.0, -8.66,
        0.0, 0.0,  5.0, -8.66,  3.42, -9.4,
        0.0, 0.0,  3.42, -9.4,  1.74, -9.85,
        0.0, 0.0,  1.74, -9.85,  0.0, -10.0,
        0.0, 0.0,  0.0, -10.0,  -1.74, -9.85,
        0.0, 0.0,  -1.74, -9.85,  -3.42, -9.4,
        0.0, 0.0,  -3.42, -9.4,  -5.0, -8.66,
        0.0, 0.0,  -5.0, -8.66,  -6.43, -7.66,
        0.0, 0.0,  -6.43, -7.66,  -7.66, -6.43,
        0.0, 0.0,  -7.66, -6.43,  -8.66, -5.0,
        0.0, 0.0,  -8.66, -5.0,  -9.4, -3.42,
        0.0, 0.0,  -9.4, -3.42,  -9.85, -1.74,
        0.0, 0.0,  -9.85, -1.74,  -10.0, 0.0,
        0.0, 0.0,  -10.0, 0.0,  -9.85, 1.74,
        0.0, 0.0,  -9.85, 1.74,  -9.4, 3.42,
        0.0, 0.0,  -9.4, 3.42,  -8.66, 5.0,
        0.0, 0.0,  -8.66, 5.0,  -7.66, 6.43,
        0.0, 0.0,  -7.66, 6.43,  -6.43, 7.66,
        0.0, 0.0,  -6.43, 7.66,  -5.0, 8.66,
        0.0, 0.0,  -5.0, 8.66,  -3.42, 9.4,
        0.0, 0.0,  -3.42, 9.4,  -1.74, 9.85,
        0.0, 0.0,  -1.74, 9.85,  0.0, 10.0
    };
};

#endif