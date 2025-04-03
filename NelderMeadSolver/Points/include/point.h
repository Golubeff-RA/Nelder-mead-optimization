#pragma once
#include <vector>
#include <initializer_list>

class Point {
public:
    Point(size_t dimensions);
    Point(const std::vector<double>& data);
    Point(std::initializer_list<double>&& data);
    // rule of 5 realisation //
    Point(const Point& other);
    Point(Point&& other);
    Point& operator=(const Point& other);

    Point& operator=(Point&& other);
    ~Point();
    // ... //

    size_t Size() const;
    double operator[](size_t idx) const;

    double& operator[](size_t idx);

    Point& operator+=(const Point& other);

    Point& operator-=(const Point& other);

    Point& operator*=(double coef);

    friend Point operator+(const Point& left, const Point& right);

    friend Point operator-(const Point& left, const Point& right);

    friend Point operator*(const Point& point, double coef);

    friend Point operator*(double coef, const Point& point);


private:
    std::vector<double> data_;
};

// вычисляет меру симплекса с помощью определителя матрицы
double Measure(const std::vector<Point>& simplex);
bool CheckDimensions(const std::vector<Point>& simplex);
double Factorial (size_t n);
double Determinant(const std::vector<std::vector<double>>& matrix);