#include "function.h"

int main()
{
    std::string expression = "-1*(-x1)";
    //std::cout <<"\n\n" << (sin(20) * cos(10) - tan(10)) * tan(10) <<"\n\n";
    std::vector<double> p = {10, 10, 10};
    Point point(p);
    std::cout << "start";
    Function func(expression);

    std::cout << func.Calculate(point);
}

