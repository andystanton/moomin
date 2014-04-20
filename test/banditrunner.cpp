#include "BanditWithGmock.h"

using namespace bandit;

int adder(int a, int b) {
    return a + b;
}

go_bandit([](){
    describe("an adder:", [](){
      it("adds two numbers together", [&](){
        AssertThat(adder(4, 7), Equals(11));
      });
    });

    describe("a multiplier:", [](){
      it("multiplies two numbers together", [&](){
        AssertThat(multiplier(4, 7), Equals(28));
      });
    });
});


int main(int argc, char* argv[]) {
    return bandit_with_gmock::run(argc, argv);
}