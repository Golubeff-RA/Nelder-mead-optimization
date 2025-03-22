#include "Function.h"

int main()
{
    std::string expression = "(x1 + x2) * x3 / x4";
    std::vector<double> p = {1,1,2,10};
    Point point(p);
    std::cout << "start";
    Function func(expression);


    std::cout << func.Calculate(point);
}

