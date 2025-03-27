#include "function.h"

Function::Function(std::string expression) : expression_(expression) {
    if (expression.size() == 0) {
        throw std::runtime_error("Empty expression\n");
    }
    PostStringTransfer ps(expression_);
    vecOperand_ = ps.GetPostfixString();
}

double Function::Calculate(Point& point) {
    return PostStringCalculater(vecOperand_).Calculate(point);
}