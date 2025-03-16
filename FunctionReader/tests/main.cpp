#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"


TEST(UnoMinusOprations, test1)
{
    std::string expression = "-5";
    Point point({});
    double ans = -5;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(UnoMinusOprations, test2)
{
    std::string expression = "-x1";
    std::vector<double> p = {1};
    Point point(p);
    double ans = -1;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(UnoMinusOprations, test3)
{
    std::string expression = "-x1";
    std::vector<double> p = {-1};
    Point point(p);
    double ans = 1;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}


TEST(SimpleOperations, test1)
{
    std::string expression = "1 + 2";
    std::vector<double> p = {};
    Point point(p);
    double ans = 3;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(SimpleOperations, test2)
{
    std::string expression = "  1 -2 ";
    std::vector<double> p = {};
    Point point(p);
    double ans = -1;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(SimpleOperations, test3)
{
    std::string expression = "10 * x1 / 2";
    std::vector<double> p = {3};
    Point point(p);
    double ans = 15;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}


TEST(SimpleOperations, test4)
{
    std::string expression = "10 / x1";
    std::vector<double> p = {4};
    Point point(p);
    double ans = 2.5;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(SimpleOperations, test5)
{
    std::string expression = "x1^x2";
    std::vector<double> p = {3,3};
    Point point(p);
    double ans = 27;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(WithScobkaOperations, test1)
{
    std::string expression = "1 + (1 + 2)";
    std::vector<double> p = {};
    Point point(p);
    double ans = 4;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(WithScobkaOperations, test2)
{
    std::string expression = " (20 / 4) / (1 -2) ";
    std::vector<double> p = {};
    Point point(p);
    double ans = -5;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(WithScobkaOperations, test3)
{
    std::string expression = "10 * (x1 + x2)";
    std::vector<double> p = {3, 5};
    Point point(p);
    double ans = 80;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(WithScobkaOperations, test4)
{
    std::string expression = "(x1)";
    std::vector<double> p = {3};
    Point point(p);
    double ans = 3;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(WithScobkaOperations, test5)
{
    std::string expression = "(x1 - 1)^(x2 + 1)";
    std::vector<double> p = {3, 3};
    Point point(p);
    double ans = 16;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(WithScobkaOperations, test6)
{
    std::string expression = "(11)";
    std::vector<double> p = {};
    Point point(p);
    double ans = 11;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(WithScobkaOperations, test7)
{
    std::string expression = "(-6)";
    std::vector<double> p = {};
    Point point(p);
    double ans = -6;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(WithScobkaOperations, test8)
{
    std::string expression = "-1*(-x1)";
    std::vector<double> p = {4};
    Point point(p);
    double ans = 4;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(DifferentOperations, test1)
{
    std::string expression = "x1 + (5 - 6) * 0 +   x2 ^ 1 + 5.5";
    std::vector<double> p = {0, 1};
    Point point(p);
    double ans = 6.5;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

TEST(DifferentOperations, test2)
{
    std::string expression = "(2 * (2 * (2 * (2 * (1 + 1)))))";
    std::vector<double> p = {};
    Point point(p);
    double ans = 32;
    Function func(expression, point);
    ASSERT_EQ(func.Calculate(), ans);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}