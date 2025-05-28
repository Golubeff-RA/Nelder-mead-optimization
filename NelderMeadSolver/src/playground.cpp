#include <iostream>

#include "solver.h"

std::vector<std::string> Split(const std::string& string, const std::string& delimiter = " ") {
    std::vector<std::string> out;

    if (string.empty()) {
        return out;
    }

    size_t lastpos1 = 0;
    while (string.find(delimiter, lastpos1) != std::string::npos) {
        size_t lastpos2 = string.find(delimiter, lastpos1);
        out.push_back(string.substr(lastpos1, lastpos2 - lastpos1));
        lastpos1 = lastpos2 + delimiter.size();
    }
    out.push_back(string.substr(lastpos1, string.size() - lastpos1));

    return out;
}

int main(int argc, char* argv[]) {
    LoggerPtr logger = Logger::GetLogger();
    NelderMeadSolver solv1(logger);
    NelderMeadSolver solv2(logger);
    NelderMeadSolver solv3(logger);

    solv1.Optimize({"x1 + x2 + x3", 100, 0.1, Point{0, 34, 89}});
    solv2.Optimize({"abs(x1 + x2)", 50, 0.001, Point{60, 80}});
    solv3.Optimize({"x1^2 + x2^2", 200, 0, Point{60, 80}});
    return 0;
}