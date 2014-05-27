#ifndef _MOOMIN_FLOATING_POINT_HELPER
#define _MOOMIN_FLOATING_POINT_HELPER

#include <cmath>
#include <limits>
#include <algorithm>

namespace floatingPointHelper {
    const static int DEFAULT_ULP = 3;

    bool almostEqual(float x, float y, int ulp = DEFAULT_ULP);

    bool lessThanOrAlmostEqual(float x, float y, int ulp = DEFAULT_ULP);
    bool moreThanOrAlmostEqual(float x, float y, int ulp = DEFAULT_ULP);

    bool significantlyLessThan(float x, float y, int ulp = DEFAULT_ULP);
    bool significantlyMoreThan(float x, float y, int ulp = DEFAULT_ULP);
};

#endif
