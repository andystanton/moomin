#ifndef _MOOMIN_SYSTEM
#define _MOOMIN_SYSTEM

#include "drawing/EntityRenderer.h"

class System
{
public:
    System();
    ~System();
private:
    EntityRenderer renderer;
};

#endif
