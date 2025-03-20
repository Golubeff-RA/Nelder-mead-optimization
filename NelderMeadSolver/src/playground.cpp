#include <iostream>
#include <vector>
#include "point.h"
#include "solver.h"

int main() {
    NelderMeadSolver solv{10e-5, 100};
    std::string func("(x1 + x2) * x3 / x4");
    Function f(func);
    Point point{1, 1, 2, 10};
    std::cout << f.Calculate(point);
    return 0;
}