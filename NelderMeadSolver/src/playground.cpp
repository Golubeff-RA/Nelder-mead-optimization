#include <iostream>
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
    NelderMeadSolver solv{10e-5, 100};

    solv.Optimize("x1^2 + x1 * x2 + x2^2 - 6*x1 - 9*x2", Point{{3, 5}});
    auto log = solv.GetLogs("x1^2 + x1 * x2 + x2^2 - 6*x1 - 9*x2");
    for (auto l : log) {
        std::cout << "Q(X) = " << l.func_val << " measure = " << l.measure << std::endl;
        for (auto p : l.points) {
            std::cout << "   ";
            PrintPoint(p);
            std::cout << "\n";
        }
    }

    return 0;
}