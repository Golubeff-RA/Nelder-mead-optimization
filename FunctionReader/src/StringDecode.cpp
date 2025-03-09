

#include "Function.h"

int main()
{
    Function func(" (x1 + x2) * x3 / x4", {1, 1, 2, 10});

    func.Decode();
    func.Print();

    std::cout << std::endl << func.Calculate();
}

