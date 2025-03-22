#pragma once
#include "PostStringCalculater.h"
#include "PostStringTransfer.h"

class Function {
private:
    std::string expression_;
    std::vector<std::string> vecOperand_;

public:
    Function(std::string expression);
    double Calculate(Point& point);
};

///////////////////////////////////////////////////////////////////////////////////

Function::Function(std::string expression)
    : expression_(expression){
    if(expression.size() == 0){
        throw std::runtime_error("Empty expression\n");
    }
    vecOperand_ = PostStringTransfer(expression).GetPostfixString();
}

double Function::Calculate(Point& point) {
    return PostStringCalculater(vecOperand_).Calculate(point);
}