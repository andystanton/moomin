#include <bandit/bandit.h>

#include "util/FloatingPointHelper.h"

using namespace bandit;

go_bandit([]()
{
    describe("a Floating Point Helper", []()
    {
        it("equates similar floats", [&]()
        {
            float val1 = 5;
            float val2 = 5.000001;

            AssertThat((val1 == val2), Is().False());
            AssertThat(floatingPointHelper::almostEqual(val1, val2), Is().True());
        });

        it("compares floats", [&]()
        {
            float val1 = 5;
            float val2 = 5.000001;

            float control = 3432;

            AssertThat(floatingPointHelper::significantlyLessThan(val1, val2), Is().False());
            AssertThat(floatingPointHelper::significantlyLessThan(val2, val1), Is().False());

            AssertThat(floatingPointHelper::lessThanOrAlmostEqual(val1, val2), Is().True());
            AssertThat(floatingPointHelper::lessThanOrAlmostEqual(val2, val1), Is().True());

            AssertThat(floatingPointHelper::significantlyLessThan(val1, control), Is().True());
            AssertThat(floatingPointHelper::significantlyLessThan(val2, control), Is().True());

            AssertThat(floatingPointHelper::significantlyMoreThan(val1, val2), Is().False());
            AssertThat(floatingPointHelper::significantlyMoreThan(val2, val1), Is().False());

            AssertThat(floatingPointHelper::significantlyMoreThan(control, val1), Is().True());
            AssertThat(floatingPointHelper::significantlyMoreThan(control, val2), Is().True());
        });
    });
});
