#include <gtest/gtest.h>
#include <iostream>
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

bool ComparePoints(const Point& left, const Point& right) {
    if (left.Size() != right.Size()) {
        return false;
    }

    for (size_t idx = 0; idx < left.Size(); ++idx) {
        if (left[idx] != right[idx]) {
            return false;
        }
    }

    return true;
}

TEST(Constructors, test) {
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

TEST(Operators, assignment) {
    Point data{{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    Point test1 = data;
    EXPECT_TRUE(ComparePoints(test1, data));
}

TEST(Operators, plus) {
    Point left{{1, 0, 1, 0, 1}};
    Point right{{0, 1, 0, 1, 0}};
    Point result{{1, 1, 1, 1, 1}};
    EXPECT_TRUE(ComparePoints((left + right), result));
    left += right;
    EXPECT_TRUE(ComparePoints(left, result));
}

TEST(Operators, minus) {
    Point left{{1, 0, 1, 0, 1}};
    Point right{{0, 1, 0, 1, 0}};
    Point result{{1, -1, 1, -1, 1}};
    EXPECT_TRUE(ComparePoints((left - right), result));
    left -= right;
    EXPECT_TRUE(ComparePoints(left, result));
}

TEST(Operators, multiply) {
    Point test{{1, 2, 3, 4, 5, 6}};
    Point rslt{{2, 4, 6, 8, 10, 12}};
    EXPECT_TRUE(ComparePoints(test * 2, rslt));
    EXPECT_TRUE(ComparePoints(2 * test, rslt));
    test *= 2;
    EXPECT_TRUE(ComparePoints(test, rslt));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}