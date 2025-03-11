#pragma once
#include <vector>

class Point {
public:
    Point(size_t dimensions) {
        data_ = std::vector<double>(dimensions, 0.0);
    }

    Point(const std::vector<double>& data) : data_(data) {
    }

    size_t Size() const {
        return data_.size();
    }

    double operator[](size_t idx) const {
        return data_[idx];
    }

    double& operator[](size_t idx) {
        return data_[idx];
    }

private:
    std::vector<double> data_;
};