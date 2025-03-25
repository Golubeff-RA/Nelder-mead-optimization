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

#include "Function.h"
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
        //size_t dim_size = CountDim(function);
        //Function func{function};
        return eps_ * epoch_;
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

    // генерирует опорный симплекс
    std::vector<Point> GenerateSimplex(size_t dim, const Point& start_point) {
        std::vector<Point> simplex;
        simplex.push_back(start_point);

        for (size_t idx = 1; idx <= dim; ++idx) {
            Point point(start_point);
            point[idx - 1] = point[idx - 1] + 1.0;
            simplex.push_back(point);
        }

        return simplex;
    }

private:
    std::map<std::string, std::list<Log>> optimized_functions_;
    const double eps_;
    const size_t epoch_;
    std::random_device rnd_device;
    // оператор сжатия

    // оператор растяжения
};