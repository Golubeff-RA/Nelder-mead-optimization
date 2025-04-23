#include <iostream>
#include <regex>
#include <vector>
#include "point.h"
#include "solver.h"

void PrintPoint (const Point& p) {
    std::cout << "(";
    for (size_t idx = 0; idx < p.Size(); ++idx) {
        std::cout << p[idx] << ", ";
    }  
    std::cout << ")";
}

int main() {
    NelderMeadSolver solv{10e-30, 500};
    solv.Optimize("x1^2 + x2^2 + x3^2 + x4^2 + x5^2 + x6^2 + x7^2 + x8^2", Point{{10, 11, 12, 13, 14, 15, 9, 7}});
    auto log = solv.GetLogs("x1^2 + x2^2 + x3^2 + x4^2 + x5^2 + x6^2 + x7^2 + x8^2");
    auto l = std::prev(log.end());
    std::cout << "Q(X) = " << l->func_val << " measure = " << l->measure << std::endl;
    solv.Optimize("x1^2 + x2^2", Point{{17, 11}});
    log = solv.GetLogs("x1^2 + x2^2");
    l = std::prev(log.end());
    std::cout << "Q(X) = " << l->func_val << " measure = " << l->measure << std::endl;
    solv.Optimize("x1 + x2", Point{{0, 0}});
    log = solv.GetLogs("x1 + x2");
    l = std::prev(log.end());
    std::cout << "Q(X) = " << l->func_val << " measure = " << l->measure << std::endl;
    return 0;
}