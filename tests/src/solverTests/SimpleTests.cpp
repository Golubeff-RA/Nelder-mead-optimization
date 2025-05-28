#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "solver.h"

TEST(CountDim, test) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);
    EXPECT_EQ(solv.CountDim("x1 + x2 + x3 + x4"), 4);
}

TEST(OptimizeTest, test1) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);
    int cnt_launch = 10;
    std::string expr = "x1 ^ 2 + x2 ^ 2";
    std::vector<double> p = {1, 1};
    Point point(p);
    double err = 10e-2;
    double ans = 0;

    double res = solv.Optimize({expr, 100, 0, p});
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize({expr, 100, 0, p}));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}

TEST(OptimizeTest, test2) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);
    int cnt_launch = 10;
    std::string expr = "abs(x1) + sin(x2)";
    std::vector<double> p = {1, 1};
    Point point(p);
    double err = 10e-2;
    double ans = -1;

    double res = solv.Optimize({expr, 100, 0, p});
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize({expr, 100, 0, p}));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}

TEST(OptimizeTest, test3) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);
    int cnt_launch = 10;
    std::string expr = "abs(x1) + abs(x2) + abs(x3) + abs(x4)";
    std::vector<double> p = {1, 1, 1, 1};
    Point point(p);
    double err = 10e-2;
    double ans = 0;

    double res = solv.Optimize({expr, 100, 0, p});
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize({expr, 100, 0, p}));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}

TEST(OptimizeTest, test4) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);
    int cnt_launch = 10;
    std::string expr = "abs(x1 ^ (2 * (abs(x2) + 1)))";
    std::vector<double> p = {1, 1};
    Point point(p);
    double err = 10e-2;
    double ans = 0;

    double res = solv.Optimize({expr, 100, 0, p});
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize({expr, 100, 0, p}));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}

TEST(OptimizeTest, test5) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);
    int cnt_launch = 10;
    std::string expr = "-cos(x1)";
    std::vector<double> p = {1};
    Point point(p);
    double err = 10e-2;
    double ans = -1;

    double res = solv.Optimize({expr, 100, 0, p});
    for (int i = 1; i< cnt_launch; i++) {
        res = std::min(res, solv.Optimize({expr, 100, 0, p}));
    }
    EXPECT_TRUE(abs(res - ans) < err);
}