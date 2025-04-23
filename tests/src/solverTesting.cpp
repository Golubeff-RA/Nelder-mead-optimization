#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "solver.h"

TEST(CountDim, test) {
  NelderMeadSolver solv(10e-2, 100);
  EXPECT_EQ(solv.CountDim("x1 + x2 + x3 + x4"), 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}