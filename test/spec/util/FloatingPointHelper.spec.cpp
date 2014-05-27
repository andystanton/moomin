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
    });
});
