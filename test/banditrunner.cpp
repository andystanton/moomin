#include "BanditWithGmock.h"

using ::testing::Return;

int main(int argc, char* argv[]) {
    return bandit_with_gmock::run(argc, argv);
}