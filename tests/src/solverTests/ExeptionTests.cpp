#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "solver.h"
#include "logger.h"


TEST(ExeptionTests, test1) {
    std::string expr = "x1 + x3";
    std::vector<double> p(3, 10);
    Point point(p);
    LoggerPtr logger = Logger::GetLogger();
    NelderMeadSolver solv(logger);
    
    try{
        solv.Optimize({expr, 100, 0, p});
        FAIL();
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("Wrong variable numerization!", e.what());
    }   
}

TEST(ExeptionTests, test2) {
    std::string expr = "xa + x3";
    std::vector<double> p(3, 10);
    Point point(p);
    LoggerPtr logger = Logger::GetLogger();
    NelderMeadSolver solv(logger);
    
    try{
        solv.Optimize({expr, 100, 0, p});
        FAIL();
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("invalid variable name", e.what());
    }   
}

TEST(ExeptionTests, test3) {
    std::string expr = "x + x3";
    std::vector<double> p(3, 10);
    Point point(p);
    LoggerPtr logger = Logger::GetLogger();
    NelderMeadSolver solv(logger);
    
    try{
        solv.Optimize({expr, 100, 0, p});
        FAIL();
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("invalid variable name", e.what());
    }   
}
