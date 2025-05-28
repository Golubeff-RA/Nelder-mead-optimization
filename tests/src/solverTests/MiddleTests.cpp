#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "solver.h"


TEST(MiddleOptimizeTest, test1) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);
    std::string expr = "abs(x1 - x2) / (x3 ^ 10 + 2) - cos(x4 * x5 / (abs(x6) + 0.11)) + ln(x7 ^ 4 + 1) + x8 ^ 2";
    double err = 10e-1;
    double ans = -1;
    Point p{{8, 10, 10, 30, 10, 40, 10, 40}};
    int cnt_launch = 4;
    double res = solv.Optimize({expr, 500, 0, p});
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize({expr, 100, 0, p}));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}

TEST(MiddleOptimizeTest, test2) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);
    std::string expr = "(x1 + x2) * (x3 + x4) / ((x3 + x4) * (x1 + x2))";
    double err = 10e-2;
    double ans = 1;
    Point p{{10, 20, 15, 30}};
    int cnt_launch = 10;
    double res = solv.Optimize({expr, 100, 0, p});
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize({expr, 100, 0, p}));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}