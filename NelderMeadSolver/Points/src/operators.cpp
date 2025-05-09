#include "point.h"

std::size_t Point::Size() const {
    return data_.size();
}

double Point::operator[](std::size_t idx) const {
    return data_[idx];
}

double& Point::operator[](std::size_t idx) {
    return data_[idx];
}

Point& Point::operator+=(const Point& other) {
    if (Size() == other.Size()) {
        for (std::size_t idx = 0; idx < Size(); ++idx) {
            (*this)[idx] += other[idx];
        }
    }

    return *this;
}

Point& Point::operator-=(const Point& other) {
    if (Size() == other.Size()) {
        for (std::size_t idx = 0; idx < Size(); ++idx) {
            (*this)[idx] -= other[idx];
        }
    }

    return *this;
}

Point& Point::operator*=(double coef) {
    for (double& dim : data_) {
        dim *= coef;
    }

    return *this;
}

Point operator+(const Point& left, const Point& right) {
    return Point(left) += right;
}

Point operator-(const Point& left, const Point& right) {
    return Point(left) -= right;
}

Point operator*(const Point& point, double coef) {
    return Point(point) *= coef;
}

Point operator*(double coef, const Point& point) {
    return Point(point) * coef;
}

