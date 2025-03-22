#pragma once
#include<stack>
#include<iostream>
#include<unordered_map>
#include<string>
#include<math.h>
#include <sstream>
#include <iomanip>
#include"point.h"

#define PLUS 0
#define MINUS 1
#define MULT 3
#define DIVIDER 4
#define POWER 5


std::unordered_map<std::string, int> caseMap_ = {
    { "+", PLUS },
    { "-", MINUS },
    { "*", MULT },
    { "/", DIVIDER },
    { "^", POWER}
};

std::unordered_map<std::string, int> operationMap_ = {
    { "(", 0 },
    { ")", 0 },
    { "+", 1 },
    { "-", 2 },
    { "*", 3 },
    { "/", 3 },
    { "^", 4}
 };

bool CheckOperandsMore(std::string operand1, std::string operand2) { return operationMap_[operand1] >= operationMap_[operand2]; }

bool IsOperation(std::string operand) { return (operationMap_.count(operand) != 0 && operand != "(" && operand != ")"); }

bool IsOperation(char operand) { return operand =='+' || operand =='-' || operand =='*' || operand =='/' || operand == '^'; }

double Calc(std::string operation, double number1, double number2){
    switch (caseMap_[operation])
    {
    case PLUS:
        return number1 + number2;
    case MINUS:
        return number1 - number2;
    case MULT:
        return number1 * number2;
    case DIVIDER:
        if (number2 == 0)
        {
            throw std::runtime_error("Math error: Attempted to divide by Zero\n");
        }
        else
        {
            return number1 / number2;
        }
    case POWER:
        return std::pow(number1, number2);
    default:
        throw std::runtime_error("Invalide operation\n");
    }
}