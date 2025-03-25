#pragma once

#include <vector>
#include <string>
#include <map>
#include <list>
#include "Function.h"
#include "point.h"

struct Log {
    std::vector<Point> points; // точки симплекса
    double measure;            // мера симплекса
    double func_val;           // значение функции
};

class NelderMeadSolver {
public:
    // тут крафтится заглушка для возможности написания фронтенда
    // не забудь удалить потом!!!
    // в нем лежит лог для функции "x1 + x2"
    NelderMeadSolver() {
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
    // вернёт найденный минимум функции
    double Optimize(const std::string& function);

    // вернёт логи процесса оптимизации функции
    std::list<Log> GetLogs(const std::string& function) {
        return optimized_functions_.at(function);
    }

private:
    std::map<std::string, std::list<Log>> optimized_functions_;
};