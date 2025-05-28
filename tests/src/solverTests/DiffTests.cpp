#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solver.h"

TEST(DiffTest, SquareTest) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    srand(time(0));
    SLV::NelderMeadSolver solv(logger);

    double ans = 0.0;
    double err = 10e-1;
    for (int i = 0; i < 30; i++) {
        std::vector<double> p = {(double)(rand() % 2000 - 1000) / 100,
                                 (double)(rand() % 2000 - 1000) / 100};
        double res = solv.Optimize({"x1^2 + x2^2", 100, 0, Point(p)});
        EXPECT_TRUE(abs(res - ans) < err);

    }
}

TEST(DiffTest, RosenbrokeTest) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    srand(time(0));
    std::string expr = "(1 - x1)^2 + 100 * (x2 - x1^2)^2";
    SLV::NelderMeadSolver solv(logger);

    double ans = 0.0;
    double err = 10e-1;

    for (int i = 0; i < 30; i++) {
        std::vector<double> p = {(double)(rand() % 2000 - 1000) / 100,
                                 (double)(rand() % 2000 - 1000) / 100};
        double res = solv.Optimize({expr, 100, 0, Point(p)});
        EXPECT_TRUE(abs(res - ans) < err);

    }
}

TEST(DiffTest, ButeTest) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    srand(time(0));
    std::string expr = "(x1 + x2 - 7)^2 + (2 * x1 + x2 - 5)^2";
    SLV::NelderMeadSolver solv(logger);

    double ans = 0.0;
    double err = 10e-1;

    for (int i = 0; i < 30; i++) {
        std::vector<double> p = {(double)(rand() % 2000 - 1000) / 100,
                                 (double)(rand() % 2000 - 1000) / 100};
        double res = solv.Optimize({expr, 100, 0, Point(p)});
        EXPECT_TRUE(abs(res - ans) < err);

    }
}

TEST(DiffTest, ConstTest) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    srand(time(0));
    std::string expr = "5";
    SLV::NelderMeadSolver solv(logger);

    double ans = 5.0;
    double err = 10e-1;

    for (int i = 0; i < 30; i++) {
        std::vector<double> p = {(double)(rand() % 2000 - 1000) / 100,
                                 (double)(rand() % 2000 - 1000) / 100};
        double res = solv.Optimize({expr, 100, 0, Point(p)});
        EXPECT_TRUE(abs(res - ans) < err);

    }
}

TEST(DiffTest, HimellblayTest) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    srand(time(0));
    std::string expr = "(x1 ^ 2 + x2 - 11) ^ 2 + (x1 + x2 ^ 2 - 7) ^ 2";
    SLV::NelderMeadSolver solv(logger);

    double ans = 0.0;
    double err = 10e-1;

    for (int i = 0; i < 30; i++) {
        std::vector<double> p = {(double)(rand() % 2000 - 1000) / 100,
                                 (double)(rand() % 2000 - 1000) / 100};
        double res = solv.Optimize({expr, 100, 0, Point(p)});
        EXPECT_TRUE(abs(res - ans) < err);
    }
    
}

TEST(DiffTest, RastriginTest) {
    SLV::LoggerPtr logger = Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);
    srand(time(0));
    std::string expr = "20 + (x1^2 - 10 * cos(2*pi*x1)) + (x2 ^ 2 - 10 * cos(2 * pi * x2))";
    
    
    double ans = 0.0;
    double err = 10e-1;
    
    for(int i = 0; i < 30; i++) {
    std::vector<double> p = {(double)(rand() % 2000 -1000) / 100, (double)(rand() % 2000 -1000) / 100};
    Point point(p);
    double res = solv.Optimize({expr, 100, 0, p});
    EXPECT_TRUE(abs(res - ans) < err);
    }
}
