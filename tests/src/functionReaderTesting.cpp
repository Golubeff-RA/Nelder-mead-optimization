#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "function.h"


TEST(UnoMinusOprations, test1)
{
    std::string expression = "-5";
    Point point({});
    double ans = -5;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(UnoMinusOprations, test2)
{
    std::string expression = "-x1";
    std::vector<double> p = {1};
    Point point(p);
    double ans = -1;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(UnoMinusOprations, test3)
{
    std::string expression = "-x1";
    std::vector<double> p = {-1};
    Point point(p);
    double ans = 1;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}


TEST(SimpleOperations, test1)
{
    std::string expression = "1 + 2";
    std::vector<double> p = {};
    Point point(p);
    double ans = 3;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(SimpleOperations, test2)
{
    std::string expression = "  1 -2 ";
    std::vector<double> p = {};
    Point point(p);
    double ans = -1;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(SimpleOperations, test3)
{
    std::string expression = "10 * x1 / 2";
    std::vector<double> p = {3};
    Point point(p);
    double ans = 15;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}


TEST(SimpleOperations, test4)
{
    std::string expression = "10 / x1";
    std::vector<double> p = {4};
    Point point(p);
    double ans = 2.5;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(SimpleOperations, test5)
{
    std::string expression = "x1^x2";
    std::vector<double> p = {3,3};
    Point point(p);
    double ans = 27;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(WithScobkaOperations, test1)
{
    std::string expression = "1 + (1 + 2)";
    std::vector<double> p = {};
    Point point(p);
    double ans = 4;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(WithScobkaOperations, test2)
{
    std::string expression = " (20 / 4) / (1 -2) ";
    std::vector<double> p = {};
    Point point(p);
    double ans = -5;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(WithScobkaOperations, test3)
{
    std::string expression = "10 * (x1 + x2)";
    std::vector<double> p = {3, 5};
    Point point(p);
    double ans = 80;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(WithScobkaOperations, test4)
{
    std::string expression = "(x1)";
    std::vector<double> p = {3};
    Point point(p);
    double ans = 3;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(WithScobkaOperations, test5)
{
    std::string expression = "(x1 - 1)^(x2 + 1)";
    std::vector<double> p = {3, 3};
    Point point(p);
    double ans = 16;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(WithScobkaOperations, test6)
{
    std::string expression = "(11)";
    std::vector<double> p = {};
    Point point(p);
    double ans = 11;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(WithScobkaOperations, test7)
{
    std::string expression = "(-6)";
    std::vector<double> p = {};
    Point point(p);
    double ans = -6;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(WithScobkaOperations, test8)
{
    std::string expression = "-1*(-x1)";
    std::vector<double> p = {4};
    Point point(p);
    double ans = 4;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(DifferentOperations, test1)
{
    std::string expression = "x1 + (5 - 6) * 0 +   x2 ^ 1 + 5.5";
    std::vector<double> p = {0, 1};
    Point point(p);
    double ans = 6.5;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(DifferentOperations, test2)
{
    std::string expression = "(2 * (2 * (2 * (2 * (1 + 1)))))";
    std::vector<double> p = {};
    Point point(p);
    double ans = 32;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}

TEST(ExeptionTest, test1)
{
    std::string expression = "1 / x1";
    std::vector<double> p = {0};
    Point point(p);
    Function func(expression);
    try{
        func.Calculate(point);
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("(Math error) Attempted to divide by Zero\n", e.what());
    }    
}

TEST(ExeptionTest, test2)
{
    std::string expression = " / x1";
    std::vector<double> p = {0};
    Point point(p);
    Function func(expression);
    try{
        func.Calculate(point);
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("Incorrect expression\n", e.what());
    }
}

TEST(ExeptionTest, test3)
{
    std::string expression = " ( 1 + 4 ) * (3 + (4)";
    std::vector<double> p = {0};
    Point point(p);
    try{
        Function func(expression);
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("Incorrect count sckob\n", e.what());
    }
}

TEST(ExeptionTest, test4)
{
    std::string expression = " ) 4 + 6";
    std::vector<double> p = {0};
    Point point(p);
    try{
        Function func(expression);
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("Incorrect count sckob\n", e.what());
    }
}

TEST(ExeptionTest, test5)
{
    std::string expression = "10 / (x1 + 6 - 6 * 4)";
    std::vector<double> p = {18};
    Point point(p);
    Function func(expression);
    try{
        func.Calculate(point);
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("(Math error) Attempted to divide by Zero\n", e.what());
    }    
}

TEST(ExeptionTest, test6)
{
    std::string expression = "";
    std::vector<double> p = {18};
    Point point(p);
    try{
        Function func(expression);
        func.Calculate(point);
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("Empty expression\n", e.what());
    }    
}

TEST(ExeptionTest, test7)
{
    std::string expression = "12g";
    std::vector<double> p = {18};
    Point point(p);
    Function func(expression);
    try{
        func.Calculate(point);
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("Invalid number 12g", e.what());
    }    
}

TEST(ExeptionTest, test8)
{
    std::string expression = "xg";
    std::vector<double> p = {18};
    Point point(p);
    Function func(expression);
    try{
        func.Calculate(point);
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("Invalid argument xg", e.what());
    }    
}

TEST(ExeptionTest, test9)
{
    std::string expression = "1 + x10";
    std::vector<double> p = {18};
    Point point(p);
    Function func(expression);
    try{
        func.Calculate(point);
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("Invalid index x10", e.what());
    }    
}


TEST(MaximTest, test1)
{
    std::string expression = "(x1 + x2) * x3 / x4";
    std::vector<double> p = {1,1,2,10};
    Point point(p);
    double ans = 0.4;
    Function func(expression);
    ASSERT_EQ(func.Calculate(point), ans);
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}