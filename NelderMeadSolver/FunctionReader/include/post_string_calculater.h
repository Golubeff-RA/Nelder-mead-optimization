#pragma once
#include "algebra.h"

namespace FR {
    class PostStringCalculater {
    private:
        std::vector<std::string> vecExs_;
        std::stack<double> stack_;
        double Decode(const std::string& number, const Point& point);
        double DecodeNumber(const std::string& number);
        double DecodeVar(const std::string& number, const Point& point);

    public:
        PostStringCalculater(std::vector<std::string> vecExpression) : vecExs_(vecExpression) {
        }

        double Calculate(const Point& point);
    };
}