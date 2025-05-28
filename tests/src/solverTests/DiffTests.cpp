#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "solver.h"


TEST(DiffTest, SquareTest) {
    srand(time(0));
    std::string expr = "x1^2 + x2^2";
    NelderMeadSolver solv(0, 100);
    
    double ans = 0.0;
    double err = 10e-1;
    
    for(int i = 0; i < 30; i++) {
    std::vector<double> p = {(double)(rand() % 2000 -1000) / 100, (double)(rand() % 2000 -1000) / 100};
    Point point(p);
    double res = solv.Optimize(expr, p);
    EXPECT_TRUE(abs(res - ans) < err);
    }
    
}

TEST(DiffTest, RosenbrokeTest) {
    srand(time(0));
    std::string expr = "(1 - x1)^2 + 100 * (x2 - x1^2)^2";
    NelderMeadSolver solv(0, 100);
    
    double ans = 0.0;
    double err = 10e-1;
    
    for(int i = 0; i < 30; i++) {
    std::vector<double> p = {(double)(rand() % 2000 -1000) / 100, (double)(rand() % 2000 -1000) / 100};
    Point point(p);
    double res = solv.Optimize(expr, p);
    EXPECT_TRUE(abs(res - ans) < err);
    }
    
}

TEST(DiffTest, ButeTest) {
    srand(time(0));
    std::string expr = "(x1 + x2 - 7)^2 + (2 * x1 + x2 - 5)^2";
    NelderMeadSolver solv(0, 100);
    
    double ans = 0.0;
    double err = 10e-1;
    
    for(int i = 0; i < 30; i++) {
    std::vector<double> p = {(double)(rand() % 2000 -1000) / 100, (double)(rand() % 2000 -1000) / 100};
    Point point(p);
    double res = solv.Optimize(expr, p);
    EXPECT_TRUE(abs(res - ans) < err);
    }
    
}

TEST(DiffTest, ConstTest) {
    srand(time(0));
    std::string expr = "5";
    NelderMeadSolver solv(0, 100);
    
    double ans = 5.0;
    double err = 10e-1;
    
    for(int i = 0; i < 30; i++) {
    std::vector<double> p = {(double)(rand() % 2000 -1000) / 100, (double)(rand() % 2000 -1000) / 100};
    Point point(p);
    double res = solv.Optimize(expr, p);
    EXPECT_TRUE(abs(res - ans) < err);
    }
    
}


TEST(DiffTest, HimellblayTest) {
    srand(time(0));
    std::string expr = "(x1 ^ 2 + x2 - 11) ^ 2 + (x1 + x2 ^ 2 - 7) ^ 2";
    NelderMeadSolver solv(0, 100);
    
    double ans = 0.0;
    double err = 10e-1;
    
    for(int i = 0; i < 30; i++) {
    std::vector<double> p = {(double)(rand() % 2000 -1000) / 100, (double)(rand() % 2000 -1000) / 100};
    Point point(p);
    double res = solv.Optimize(expr, p);
    EXPECT_TRUE(abs(res - ans) < err);
    }
    
}
