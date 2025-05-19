#include "point.h"

Point::Point(std::size_t dimensions) {
    data_ = std::vector<double>(dimensions, 0.0);
}

Point::Point(const std::vector<double>& data) : data_(data) {
}

Point::Point(std::initializer_list<double>&& data) : data_(data) {
}