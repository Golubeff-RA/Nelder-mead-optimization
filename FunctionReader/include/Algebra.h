#pragma once
#include<unordered_map>
#include<string>
#include<math.h>

#define PLUS 0
#define MINUS 1
#define MULT 3
#define DIVIDER 4
#define POWER 5


std::unordered_map<std::string, int> caseMap = {
    { "+", PLUS },
    { "-", MINUS },
    { "*", MULT },
    { "/", DIVIDER },
    { "^", POWER}
};

std::unordered_map<std::string, int> operationMap = {
    { "(", 0 },
    { ")", 0 },
    { "+", 1 },
    { "-", 2 },
    { "*", 3 },
    { "/", 3 },
    { "^", 4}
 };

bool CheckOperandsMore(std::string operand1, std::string operand2) { return operationMap[operand1] >= operationMap[operand2]; }

bool isOperation(std::string operand) { return (operationMap.count(operand) != 0 && operand != "(" && operand != ")"); }

bool isOperation(char operand) { return operand =='+' || operand =='-' || operand =='*' || operand =='/' || operand == '^'; }

double Calc(std::string operation, double number1, double number2){
    switch (caseMap[operation])
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