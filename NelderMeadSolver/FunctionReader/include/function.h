#pragma once
#include "post_string_calculater.h"
#include "post_string_transfer.h"

namespace FR {
    class Function {
    private:
        std::string expression_;
        std::vector<std::string> vecOperand_;

    public:
        Function(const std::string expression);
        double Calculate(const Point& point);
    };
} //end FR