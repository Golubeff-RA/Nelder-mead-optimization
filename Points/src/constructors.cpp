#include "point.h"

Point::Point(size_t dimensions) {
    data_ = std::vector<double>(dimensions, 0.0);
}

Point::Point(const std::vector<double>& data) : data_(data) {
}

// rule of 5 realisation //
Point::Point(const Point& other) : data_(other.data_) {
}

Point::Point(Point&& other) : data_(std::move(other.data_)) {
}

Point& Point::operator=(const Point& other) {
    this->data_ = other.data_;
    return *this;
}

Point& Point::operator=(Point&& other) {
    this->data_ = std::move(other.data_);
    return *this;
}

Point::~Point() {
}
// ... //