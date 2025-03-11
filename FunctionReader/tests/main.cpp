#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"

TEST(TestCaseName, TestName1)
{
    Function func(" (x1 + x2)", {1, 1});
    ASSERT_EQ(func.Calculate(), 2.0);
}

TEST(TestCaseName, TestName2)
{
    Function func(" x1^ x2", {2,5});
    //func.Decode();
    ASSERT_EQ(func.Calculate(), 32);
}

TEST(TestCaseName, TestName3)
{
    Function func(" (x1*(x2+x3)/x4)", {2, 3, 2, 5});
    //func.Decode();
    ASSERT_EQ(func.Calculate(), 2);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}