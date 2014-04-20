#include "util/BanditWithGmock.h"

using namespace bandit;
using ::testing::Return;

go_bandit([](){
    describe("a test case", [](){
      it("asserts something correctly", [&](){
        
      });
    });
});


int main(int argc, char* argv[]) {
    return bandit_with_gmock::run(argc, argv);
}