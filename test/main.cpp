/*
 * This file includes the magic necessary in order to get your unit tests
 * that you create with UnitTest++ to automatically run. There should
 * never be a reason to modify this file. For an example unit test,
 * see "sanity_check.cpp". For a reference on creating tests, see "test.h".
 *
 */

 #include <gtest/gtest.h>

int adder(int a, int b) {
    return a + b;
}

TEST(AdderTest, Basic) {
  EXPECT_EQ(3, adder(1, 2));
  EXPECT_EQ(50, adder(26, 24));
}