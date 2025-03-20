#pragma once
#include <sstream>
#include <iomanip>
#include "PostStringCalculater.hpp"
#include "PostStringTransfer.h"
#include "point.h"

class Function {
private:
    std::string expression;
    std::vector<std::string> vecOperand;

public:
    Function(const std::string& expression) : expression(expression) {
        if(expression == ""){
            throw std::runtime_error("empty expression\n");
        }
        vecOperand = PostStringTransfer(expression).GetPostfixString();
    }
    double Calculate(const Point& point) {
        return PostStringCalculater(vecOperand, point).Calculate();
    }
};
