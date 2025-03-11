#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "solver.h"

TEST(Simple, kekes) {
    NelderMeadSolver test;
    EXPECT_EQ(2+2, 4);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}