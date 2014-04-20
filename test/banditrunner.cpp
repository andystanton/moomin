#include "BanditWithGmock.h"

#include <Multiplier.h>
#include <Adder.h>

using namespace bandit;

go_bandit([](){
    describe("an adder:", [](){
      Adder adder = Adder();
      it("adds two numbers together", [&](){
        AssertThat(adder.add(4, 7), Equals(11));
      });
    });

    describe("a multiplier:", [](){
      Multiplier multiplier = Multiplier();

      it("multiplies two numbers together", [&](){
        AssertThat(multiplier.multiply(4, 7), Equals(28));
      });
    });
});


int main(int argc, char* argv[]) {
    return bandit_with_gmock::run(argc, argv);
}