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
    Point start_point{{0,0,0,0}};
    auto simplex = solv.GenerateSimplex(4, start_point);
    for (auto& p : simplex) {
        PrintPoint(p);
        std::cout << "\n";
    }
    return 0;
}