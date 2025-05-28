#pragma once

#include <map>
#include <vector>
#include <initializer_list>

class Point {
public:
    Point(std::size_t dimensions = 0);
    Point(const std::vector<double>& data);
    Point(std::initializer_list<double>&& data);

    std::size_t Size() const;
    double operator[](std::size_t idx) const;

    double& operator[](std::size_t idx);

    Point& operator+=(const Point& other);

    Point& operator-=(const Point& other);

    Point& operator*=(double coef);

    friend Point operator+(const Point& left, const Point& right);

    friend Point operator-(const Point& left, const Point& right);

    friend Point operator*(const Point& point, double coef);

    friend Point operator*(double coef, const Point& point);

    static double Length(const Point& left, const Point& right);
private:
    std::vector<double> data_;
};

// вычисляет меру симплекса с помощью определителя матрицы
double LongMeasure(const std::vector<Point>& simplex);
double Measure(const std::multimap<double, Point>& simplex);
bool CheckDimensions(const std::vector<Point>& simplex);
double Factorial (std::size_t n);
double Determinant(const std::vector<std::vector<double>>& matrix);