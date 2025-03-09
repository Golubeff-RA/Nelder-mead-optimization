#pragma once
#include<unordered_map>


std::unordered_map<std::string, int> operandMap = {
    { "(", 0 },
    { ")", 0 },
    { "+", 1 },
    { "-", 2 },
    { "*", 3 },
    { "/", 3 },
 };


bool CheckOperandsMore(std::string operand1, std::string operand2) { return operandMap[operand1] >= operandMap[operand2]; }

bool isOperand(std::string operand) { return (operandMap.count(operand) != 0 && operand != "(" && operand != ")"); }

bool isOperand(char operand) { return operand =='+' || operand =='-' || operand =='*' || operand =='/'; }

double Calc(std::string operand, double number1, double number2)
    {

        if (operand == "+")
            return number1 + number2;
        if (operand == "-")
            return number1 - number2;
        if (operand == "*")
            return number1 * number2;

        if (number2 == 0)
        {
            throw std::runtime_error("Math error: Attempted to divide by Zero\n");
        }
        else
        {
            return number1 / number2;
        }
    }