#include "algebra.h"

std::map<std::string, Operation> operationMap_ = {
    {"()", Operation(SCOBKA, 0, NONE)}, {")", Operation(SCOBKA, 0, NONE)},
    {"+", Operation(PLUS, 1, BIN)},     {"-", Operation(MINUS, 2, BIN)},
    {"*", Operation(MULT, 3, BIN)},     {"/", Operation(DIVIDER, 3, BIN)},
    {"^", Operation(POWER, 4, BIN)},    {"sin", Operation(SIN, 5, UNO)},
    {"cos", Operation(COS, 5, UNO)},    {"tan", Operation(TAN, 5, UNO)},
    {"ctg", Operation(CTG, 5, UNO)},    {"ln", Operation(LN, 5, UNO)},
    {"log2", Operation(LOG2, 5, UNO)},  {"log", Operation(LOG, 5, UNO)},
    {"sqrt", Operation(SQRT, 5, UNO)},  {"abs", Operation(ABS, 5, UNO)}};

int GetTypeOperation(std::string operand) {
    return operationMap_[operand].typeOperation_;
}

bool CheckOperandsMore(std::string operand1, std::string operand2) {
    return operationMap_[operand1].priority_ >= operationMap_[operand2].priority_;
}

bool IsOperation(std::string operand) {
    return (operationMap_.count(operand) != 0 && operand != "(" && operand != ")");
}

bool IsOperation(char operand) {
    return operand == '+' || operand == '-' || operand == '*' || operand == '/' || operand == '^';
}

double Calc(std::string operation, std::vector<double>& vecNumber) {
    switch (operationMap_[operation].name_) {
        case PLUS:
            return vecNumber[1] + vecNumber[0];
        case MINUS:
            return vecNumber[1] - vecNumber[0];
        case MULT:
            return vecNumber[1] * vecNumber[0];
        case DIVIDER:
            if (vecNumber[0] == 0) {
                throw std::runtime_error("(Math error) Attempted to divide by Zero\n");
            } else {
                return vecNumber[1] / vecNumber[0];
            }
        case POWER:
            return std::pow(vecNumber[1], vecNumber[0]);
        case SIN:
            return std::sin(vecNumber[0]);
        case COS:
            return std::cos(vecNumber[0]);
        case TAN:
            return std::atan(vecNumber[0]);
        case CTG:
            if (std::atan(vecNumber[0]) == 0) {
                throw std::runtime_error("Math error: Attempted to divide by Zero\n");
            } else {
                return 1 / std::atan(vecNumber[0]);
            }
        case LN:
            if (vecNumber[0] < 0) {
                throw std::runtime_error("Less zero\n");
            }
            return std::log(vecNumber[0]);
        case LOG2:
            if (vecNumber[0] < 0) {
                throw std::runtime_error("Less zero\n");
            }
            return std::log2(vecNumber[0]);
        case LOG:
            if (vecNumber[0] < 0) {
                throw std::runtime_error("Less zero\n");
            }
            return std::log10(vecNumber[0]);
        case SQRT:
            return std::sqrt(vecNumber[0]);
        case ABS:
            return std::abs(vecNumber[0]);
        default:
            throw std::runtime_error("Invalide operation\n");
    }
}