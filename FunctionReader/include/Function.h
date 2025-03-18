#pragma once
#include <sstream>
#include <iomanip>
#include "PostStringCalculater.hpp"
#include "PostStringTransfer.h"
#include "point.h"

class Function {
private:
    std::string expression;
    Point _point;
    std::vector<std::string> vecOperand;

public:
    Function(std::string expression, Point point);
    double Calculate();
};

///////////////////////////////////////////////////////////////////////////////////

Function::Function(std::string expression, Point point)
    : expression(std::move(expression)), _point(point) {
    vecOperand = PostStringTransfer(expression).GetPostfixString();
}

double Function::Calculate() {
    return PostStringCalculater(vecOperand, _point).Calculate();
}