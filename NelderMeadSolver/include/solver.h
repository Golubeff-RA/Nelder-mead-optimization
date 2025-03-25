#pragma once

#include <algorithm>
#include <exception>
#include <list>
#include <map>
#include <random>
#include <set>
#include <string>
#include <utility>
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
    // тут крафтится заглушка для возможности написания фронтенда
    // не забудь удалить потом!!!
    // в нем лежит лог для функции "x1 + x2"
    NelderMeadSolver(double eps = 10e-5, size_t epoch = 100) : eps_(eps), epoch_(epoch) {
        std::vector<double> p_data1{1, 2};
        std::vector<double> p_data2{2, 3};
        std::vector<double> p_data3{3, 4};
        Point p1(p_data1);
        Point p2(p_data2);
        Point p3(p_data3);
        Log log1{std::vector{p1, p2, p3}, 666.0, 777.0};
        Log log2{std::vector{p1, p2, p3}, 100.0, 777.0};
        Log log3{std::vector{p1, p3, p2}, 666.0, 999.0};
        Log log4{std::vector{p3, p2, p1}, 782.0, 583.0};
        Log log5{std::vector{p1, p2, p3}, 888.0, 871.0};
        optimized_functions_["x1 + x2"] = std::list{log1, log2, log3, log4, log5};
    }

    // вернёт найденный минимум функции стартуя с заданной точки
    double Optimize(const std::string& function, const Point& start_point) {
        std::list<Log> current_optimization;
        double measure = 100;
        size_t counter = 0;
        size_t dim_size = CountDim(function);
        Function func{function};
        auto simplex{GenerateSimplex(dim_size, start_point, func)};
        while (counter < epoch_ && measure > eps_) {
            auto vec_simplex = SimplexToVector_(simplex);
            measure = Measure(vec_simplex);
            current_optimization.push_back(Log{vec_simplex, measure, simplex.begin()->first});

            Point worst{std::prev(simplex.end())->second};
            Point center{CalcCenter(simplex)};
            Point new_point = center + (center - worst);

            if (func.Calculate(new_point) < simplex.begin()->first) {
                new_point = center + expan_coef_ * (center - worst);
            } else if (func.Calculate(new_point) > func.Calculate(worst)) {
                new_point = center - contr_coef_ * (center - worst);
            }
            simplex.insert({func.Calculate(new_point), new_point});
            simplex.erase(std::prev(simplex.end()));

            ++counter;
        }

        optimized_functions_.insert({function, std::move(current_optimization)});
        return simplex.begin()->first;
    }

    // счтает переменных в оптимизируемой функции
    size_t CountDim(const std::string& function) {
        std::set<size_t> vars;
        size_t idx = 0;
        while (idx < function.size()) {
            if (function[idx] == 'x') {
                ++idx;
                std::string num{};
                while (function[idx] >= '0' && function[idx] <= '9' && idx < function.size()) {
                    num.push_back(function[idx]);
                    ++idx;
                }
                vars.insert(std::stoull(num));
            }
            ++idx;
        }

        // неверная нумерация переменных
        if (*(std::prev(vars.end())) != vars.size()) {
            throw std::runtime_error("Wrong var numerization!");
        }
        return *(std::prev(vars.end()));
    }

    // вернёт логи процесса оптимизации функции
    std::list<Log> GetLogs(const std::string& function) {
        return optimized_functions_.at(function);
    }

    Point CalcCenter(const std::multimap<double, Point>& simplex) {
        Point center(simplex.size() - 1);
        for (auto it = simplex.begin(); it != std::prev(simplex.end()); ++it) {
            center += it->second;
        }

        return center *= 1.0 / (simplex.size() - 1);
    }

    // генерирует опорный симплекс
    std::multimap<double, Point> GenerateSimplex(size_t dim, Point start_point, Function& func) {
        std::multimap<double, Point> simplex;
        simplex.insert({func.Calculate(start_point), start_point});

        for (size_t idx = 1; idx <= dim; ++idx) {
            Point point(start_point);
            point[idx - 1] = point[idx - 1] + 1.0;
            simplex.insert({func.Calculate(point), point});
        }

        return simplex;
    }

private:
    std::map<std::string, std::list<Log>> optimized_functions_;
    const double eps_;
    const size_t epoch_;
    const double expan_coef_ = 1.8;
    const double contr_coef_ = 0.3;
    const double shrnk_coef_ = 0.5;

    std::vector<Point> SimplexToVector_(const std::multimap<double, Point>& simplex) {
        std::vector<Point> points;
        points.reserve(simplex.size());
        for (auto p : simplex) {
            points.push_back(p.second);
        }

        return points;
    }

    void ShrinkSimplex_(std::multimap<double, Point>& simplex, Function& func) {
        Point best{simplex.begin()->second};
        std::vector<Point> shrinked;
        shrinked.reserve(simplex.size());
        shrinked.push_back(best);
        for (auto it = std::next(simplex.begin()); it != simplex.end(); ++it) {
            shrinked.push_back(best + shrnk_coef_ * (it->second - best));
        }

        simplex.clear();
        for (Point& p : shrinked) {
            simplex.insert({func.Calculate(p), p});
        }
    }
};