#pragma once
#include <vector>

class Point {
public:
    Point(size_t dimensions) {
        data_ = std::vector<double>(dimensions, 0.0);
        pointer_ = new double(5);
    }

    Point(const std::vector<double>& data) : data_(data) {
    }

    // rule of 5 realisation
    Point(const Point& other) : data_(other.data_) {
    }

    Point(Point&& other) : data_(std::move(other.data_)) {
    }

    Point& operator=(const Point& other) {
        this->data_ = other.data_;
        return *this;
    }

    Point& operator=(Point&& other) {
        this->data_ = std::move(other.data_);
        return *this;
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
    double* pointer_;
};