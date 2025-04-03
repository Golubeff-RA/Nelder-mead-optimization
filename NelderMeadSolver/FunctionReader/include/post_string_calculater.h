#pragma once
#include "algebra.h"

class PostStringCalculater {
private:
    std::vector<std::string> vecExs_;
    std::stack<double> stack_;
    double DecodeNumber(std::string number, Point& point);

public:
    PostStringCalculater(std::vector<std::string> vecExpression) : vecExs_(vecExpression) {
    }

    double Calculate(Point& point);
};
