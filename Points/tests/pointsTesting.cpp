#include <gtest/gtest.h>
#include <vector>
#include "point.h"

bool CompareData(const Point& p, const std::vector<double>& data) {
    if (p.Size() != data.size()) {
        return false;
    }
    for (size_t i = 0; i < data.size(); ++i) {
        if (p[i] != data[i]) {
            return false;
        }
    }
    return true;
}

TEST(Constructors, test1) {
    const size_t kSize = 5;
    std::vector<double> data1(kSize, 0);
    std::vector<double> data2{1.3, 3.5, 4.6, 4.2, 7.9};
    std::vector<double> data3{5, 6, 7, 4, 2};
    Point test1{kSize};
    Point test2{data2};
    Point test3{{5, 6, 7, 4, 2}};
    EXPECT_TRUE(CompareData(test1, data1));
    EXPECT_TRUE(CompareData(test2, data2));
    EXPECT_TRUE(CompareData(test3, data3));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}