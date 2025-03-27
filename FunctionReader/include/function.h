#pragma once
#include "post_string_calculater.h"
#include "post_string_transfer.h"

class Function {
private:
    std::string expression_;
    std::vector<std::string> vecOperand_;

public:
    Function(std::string expression);
    double Calculate(Point& point);
};
