#pragma once
#include"Definition.h"
#include"point.h"

int GetTypeOperation(std::string operand) { return operationMap_[operand].typeOperation_;}

bool CheckOperandsMore(std::string operand1, std::string operand2) { return operationMap_[operand1].priority_ >= operationMap_[operand2].priority_; }

bool IsOperation(std::string operand) { return (operationMap_.count(operand) != 0 && operand != "(" && operand != ")"); }

bool IsOperation(char operand) { return operand =='+' || operand =='-' || operand =='*' || operand =='/' || operand == '^'; }

double Calc(std::string operation, std::vector<double>& vecNumber){
    switch (operationMap_[operation].name_)
    {
    case PLUS:
        return vecNumber[1] + vecNumber[0];
    case MINUS:
        return vecNumber[1] - vecNumber[0];
    case MULT:
        return vecNumber[1] * vecNumber[0];
    case DIVIDER:
        if (vecNumber[0] == 0)
        {
            throw std::runtime_error("Math error: Attempted to divide by Zero\n");
        }
        else
        {
            return vecNumber[1] / vecNumber[0];
        }
    case POWER:
        return std::pow(vecNumber[1],  vecNumber[0]);
    case SIN:
        return std::sin(vecNumber[0]);
    case COS:
        return std::cos(vecNumber[0]); 
    case TAN:
        return std::atan(vecNumber[0]);
    case CTG:
        if (std::atan(vecNumber[0]) == 0)
        {
            throw std::runtime_error("Math error: Attempted to divide by Zero\n");
        }
        else
        {
            return 1 / std::atan(vecNumber[0]);
        }
    case LN:
        if(vecNumber[0] < 0){
            throw std::runtime_error("Less zero\n");
        }
        return std::log(vecNumber[0]);
    case LOG2:
        if(vecNumber[0] < 0){
            throw std::runtime_error("Less zero\n");
        }
        return std::log2(vecNumber[0]);
    case LOG:
        if(vecNumber[0] < 0){
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