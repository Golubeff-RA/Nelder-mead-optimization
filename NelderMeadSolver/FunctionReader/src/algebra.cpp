#include "algebra.h"

namespace FR {
    std::map<std::string, Operation> operationMap_ = {
        {"()", Operation(OPERAND::SCOBKA, 0, TYPE::NONE)}, {")", Operation(OPERAND::SCOBKA, 0, TYPE::NONE)},
        {"+", Operation(OPERAND::PLUS, 1, TYPE::BIN)},     {"-", Operation(OPERAND::MINUS, 2, TYPE::BIN)},
        {"*", Operation(OPERAND::MULT, 3, TYPE::BIN)},     {"/", Operation(OPERAND::DIVIDER, 3, TYPE::BIN)},
        {"^", Operation(OPERAND::POWER, 4, TYPE::BIN)},    {"sin", Operation(OPERAND::SIN, 5, TYPE::UNO)},
        {"cos", Operation(OPERAND::COS, 5, TYPE::UNO)},    {"tan", Operation(OPERAND::TAN, 5, TYPE::UNO)},
        {"ctg", Operation(OPERAND::CTG, 5, TYPE::UNO)},    {"ln", Operation(OPERAND::LN, 5, TYPE::UNO)},
        {"log2", Operation(OPERAND::LOG2, 5, TYPE::UNO)},  {"log", Operation(OPERAND::LOG, 5, TYPE::UNO)},
        {"sqrt", Operation(OPERAND::SQRT, 5, TYPE::UNO)},  {"abs", Operation(OPERAND::ABS, 5, TYPE::UNO)}};

    TYPE GetTypeOperation(std::string operand) {
        return operationMap_[operand].typeOperation_;
    } 

    OPERAND GetNameOperation(std::string operand){
        return operationMap_[operand].name_;
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
            case OPERAND::PLUS:
                return vecNumber[1] + vecNumber[0];
            case OPERAND::MINUS:
                switch (vecNumber.size())
                {
                case 1:
                    return -vecNumber[0];
                case 2:
                    return vecNumber[1] - vecNumber[0];
                default:
                    throw std::runtime_error("Incorect expression");
                }
            case OPERAND::MULT:
                return vecNumber[1] * vecNumber[0];
            case OPERAND::DIVIDER:
                if (vecNumber[0] == 0) {
                    throw std::runtime_error("(Math error) Attempted to divide by Zero\n");
                } else {
                    return vecNumber[1] / vecNumber[0];
                }
            case OPERAND::POWER:
                return std::pow(vecNumber[1], vecNumber[0]);
            case OPERAND::SIN:
                return std::sin(vecNumber[0]);
            case OPERAND::COS:
                return std::cos(vecNumber[0]);
            case OPERAND::TAN:
                return std::atan(vecNumber[0]);
            case OPERAND::CTG:
                if (std::atan(vecNumber[0]) == 0) {
                    throw std::runtime_error("Math error: Attempted to divide by Zero\n");
                } else {
                    return 1 / std::atan(vecNumber[0]);
                }
            case OPERAND::LN:
                if (vecNumber[0] < 0) {
                    throw std::runtime_error("Less zero\n");
                }
                return std::log(vecNumber[0]);
            case OPERAND::LOG2:
                if (vecNumber[0] < 0) {
                    throw std::runtime_error("Less zero\n");
                }
                return std::log2(vecNumber[0]);
            case OPERAND::LOG:
                if (vecNumber[0] < 0) {
                    throw std::runtime_error("Less zero\n");
                }
                return std::log10(vecNumber[0]);
            case OPERAND::SQRT:
                return std::sqrt(vecNumber[0]);
            case OPERAND::ABS:
                return std::abs(vecNumber[0]);
            default:
                throw std::runtime_error("Invalide operation\n");
        }
    }
} // end FR