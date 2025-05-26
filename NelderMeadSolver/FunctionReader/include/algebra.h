#pragma once
#include "definition.h"
#include "point.h"

namespace FR {
    TYPE GetTypeOperation(std::string operand);

    OPERAND GetNameOperation(std::string operand);

    bool CheckOperandsMore(std::string operand1, std::string operand2);

    bool IsOperation(std::string operand);

    bool IsOperation(char operand);

    double Calc(std::string operation, std::vector<double>& vecNumber);
} // end FR