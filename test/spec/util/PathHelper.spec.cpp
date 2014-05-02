#include <bandit/bandit.h>

#include "util/PathHelper.h"

using namespace bandit;

go_bandit([]() 
{
    describe("a Path Helper", []() 
    {
        PathHelper pathHelper;

        it("returns the application's path", [&]() 
        {
            AssertThat(pathHelper.getApplicationPath(), Is().Not().Empty());
        });

        it("returns the application's name", [&]() 
        {
            AssertThat(pathHelper.getApplicationName(), Is().Not().Empty());
        });
    });
});
