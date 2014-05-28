#include "util/FloatingPointHelper.h"

bool floatingPointHelper::almostEqual(float x, float y, int ulp)
{
    return std::abs(x-y) <=   std::numeric_limits<float>::epsilon()
                            * std::max(std::abs(x), std::abs(y))
                            * ulp;
}

bool floatingPointHelper::lessThanOrAlmostEqual(float x, float y, int ulp)
{
    return almostEqual(x, y, ulp) || (x < y);
}

bool floatingPointHelper::moreThanOrAlmostEqual(float x, float y, int ulp)
{
    return almostEqual(x, y, ulp) || (x > y);
}

bool floatingPointHelper::significantlyLessThan(float x, float y, int ulp)
{
    return !almostEqual(x, y, ulp) && (x < y);
}

bool floatingPointHelper::significantlyMoreThan(float x, float y, int ulp)
{
    return !almostEqual(x, y, ulp) && (x > y);
}
