#pragma once

#include <ctime>
#include <exception>
#include <list>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "function.h"
#include "logger.h"
#include "point.h"

using Simplex = std::multimap<double, Point>;

class NelderMeadSolver {
public:
    NelderMeadSolver(LoggerPtr log_ptr, double expan_coef_ = 2, double shrnk_coef = 0.5,
                     double refle_coef = 1, size_t update_simplex = 25);
    // вернёт найденный минимум функции стартуя с заданной точки
    double Optimize(const OptInfo& info);
    // вернёт строчку с гиперпараметрами оптимизации
    std::string GetHyperparams() const;
    // считает число переменных в оптимизируемой функции
    static size_t CountDim(const std::string& function);
    

private:
    const LoggerPtr log_ptr_;
    const double expan_coef_;
    const double shrnk_coef_;
    const double refle_coef_;
    const size_t update_simplex_;

    // вычисляет центр "лучших" точек симплекса
    Point CalcCenter_(const Simplex& simplex);

    // генерирует опорный симплекс
    Simplex GenerateSimplex_(size_t dim, Point start_point, FR::Function& func);

    // преобразует симплекс в вектор точек
    std::vector<Point> SimplexToVector_(const Simplex& simplex);

    // оператор локального сжатия
    void LocalShrink_(FR::Function& func, Simplex& simplex, const Point& center);

    // оператор глобального сжатия всего симплекса
    void GlobalShrink_(FR::Function& func, Simplex& simplex);
};
