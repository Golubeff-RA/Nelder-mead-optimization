#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "solver.h"
#include "logger.h"


TEST(ExeptionTests, test1) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);
    
    try{
        solv.Optimize({"x1 + x3", 100, 0, {3, 10}});

        FAIL();
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("Wrong variable numerization!", e.what());
    }   
}

TEST(ExeptionTests, test2) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);
    
    try{
        solv.Optimize({"xa + x3", 100, 0, {3, 10}});

        FAIL();
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("invalid variable name", e.what());
    }   
}

TEST(ExeptionTests, test3) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solv(logger);

    try{
        solv.Optimize({"x + x3", 100, 0, {3, 10}});
        FAIL();
    } catch (std::runtime_error &e) {
        EXPECT_STREQ("invalid variable name", e.what());
    }   
}
