#include <vector>
#include <string>
#include "Function.h"

class NelderMeadSolver {
public:
    NelderMeadSolver() {
        std::cout << "Hello from solver" << std::endl;
    }
private:
    std::string function_;
};