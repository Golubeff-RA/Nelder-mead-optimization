#include <gtest/gtest.h>
#include "logger.h"

TEST(LoggerTest, test1) {
    Logger l;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}