#include <bandit/bandit.h>
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
});

int main(int argc, char* argv[]) {
  return bandit::run(argc, argv);
}