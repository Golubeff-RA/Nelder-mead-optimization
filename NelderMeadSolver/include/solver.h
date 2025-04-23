#pragma once

#include <ctime>
#include <exception>
#include <list>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "function.h"
#include "point.h"

struct Log {
    std::vector<Point> points;  // точки симплекса
    double measure;             // мера симплекса
    double func_val;            // значение функции
};

class NelderMeadSolver {
public:
    NelderMeadSolver(double eps = 10e-5, size_t epoch = 100);

    // вернёт найденный минимум функции стартуя с заданной точки
    double Optimize(const std::string& function, const Point& start_point);

    // счтает переменных в оптимизируемой функции
    size_t CountDim(const std::string& function);

    // вернёт логи процесса оптимизации функции
    std::list<Log> GetLogs(const std::string& function);

    double eps() const;

    double& eps();

    size_t epoch() const;

    size_t& epoch();

private:
    double eps_;
    size_t epoch_;
    std::map<std::string, std::list<Log>> optimized_functions_;
    const double expan_coef_ = 2;
    const double shrnk_coef_ = 0.5;
    const double refle_coef_ = 1;
    const size_t update_simplex_ = 25;

    // вычисляет центр "лучших" точек симплекса
    Point CalcCenter_(const std::multimap<double, Point>& simplex);

    // генерирует опорный симплекс
    std::multimap<double, Point> GenerateSimplex_(size_t dim, Point start_point, Function& func);

    // преобразует симплекс в вектор точек
    std::vector<Point> SimplexToVector_(const std::multimap<double, Point>& simplex);

    // оператор локального сжатия
    void LocalShrink_(Function& func, std::multimap<double, Point>& simplex, const Point& center);

    // оператор глобального сжатия всего симплекса
    void GlobalShrink_(Function& func, std::multimap<double, Point>& simplex);
};
