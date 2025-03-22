#include "Function.h"

int main()
{
    std::string expression = "(sin(x1 + x2) * cos(x1) - tan(x2)) / ctg(x3)";
    //std::cout <<"\n\n" << (sin(20) * cos(10) - tan(10)) * tan(10) <<"\n\n";
    std::cout << "\n\n" << asin(1) <<' ' << std::atan(asin(1)) <<"\n\n";
    std::vector<double> p = {10, 10, 10};
    Point point(p);
    std::cout << "start";
    Function func(expression);


    std::cout << func.Calculate(point);
}

