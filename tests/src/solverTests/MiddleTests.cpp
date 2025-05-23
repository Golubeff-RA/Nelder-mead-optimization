#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "solver.h"


TEST(MiddleOptimizeTest, test1) {
    int cnt_launch = 1;
    std::string expr = "abs(x1 - x2) / (x3 ^ 10 + 2) - cos(x4 * x5 / (abs(x6) + 0.11)) + ln(x7 ^ 4 + 1) + x8 ^ 2";
    std::vector<double> p(8, 10);
    Point point(p);
    double err = 10e-1;
    double ans = -1;

    NelderMeadSolver solv(0, 100);
    double res = solv.Optimize(expr, p);
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize(expr, p));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}

TEST(MiddleOptimizeTest, test2) {
    int cnt_launch = 10;
    std::string expr = "(x1 + x2) * (x3 + x4) / ((x3 + x4) * (x1 + x2))";
    std::vector<double> p(4, 10);
    Point point(p);
    double err = 10e-2;
    double ans = 1;

    NelderMeadSolver solv(0, 100);
    double res = solv.Optimize(expr, p);
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize(expr, p));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}