#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "solver.h"

TEST(CountDim, test) {
    NelderMeadSolver solv(10e-2, 100);
    EXPECT_EQ(solv.CountDim("x1 + x2 + x3 + x4"), 4);
}

TEST(OptimizeTest, test1) {
    int cnt_launch = 10;
    std::string expr = "x1 ^ 2 + x2 ^ 2";
    std::vector<double> p = {1, 1};
    Point point(p);
    double err = 10e-2;
    double ans = 0;

    NelderMeadSolver solv(0, 100);
    double res = solv.Optimize(expr, p);
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize(expr, p));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}

TEST(OptimizeTest, test2) {
    int cnt_launch = 10;
    std::string expr = "abs(x1) + sin(x2)";
    std::vector<double> p = {1, 1};
    Point point(p);
    double err = 10e-2;
    double ans = -1;

    NelderMeadSolver solv(0, 100);
    double res = solv.Optimize(expr, p);
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize(expr, p));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}

TEST(OptimizeTest, test3) {
    int cnt_launch = 10;
    std::string expr = "abs(x1) + abs(x2) + abs(x3) + abs(x4)";
    std::vector<double> p = {1, 1, 1, 1};
    Point point(p);
    double err = 10e-2;
    double ans = 0;

    NelderMeadSolver solv(0, 100);
    double res = solv.Optimize(expr, p);
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize(expr, p));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}

TEST(OptimizeTest, test4) {
    int cnt_launch = 10;
    std::string expr = "abs(x1 ^ (2 * (abs(x2) + 1)))";
    std::vector<double> p = {1, 1};
    Point point(p);
    double err = 10e-2;
    double ans = 0;

    NelderMeadSolver solv(0, 100);
    double res = solv.Optimize(expr, p);
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize(expr, p));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}

TEST(OptimizeTest, test5) {
    int cnt_launch = 10;
    std::string expr = "-cos(x1)";
    std::vector<double> p = {1};
    Point point(p);
    double err = 10e-2;
    double ans = -1;

    NelderMeadSolver solv(0, 100);
    double res = solv.Optimize(expr, p);
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize(expr, p));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}