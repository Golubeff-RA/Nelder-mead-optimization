#pragma once
#include"PostStringTransfer.h"
#include<iostream>


class PostStringCalculater{
    private:
    std::vector<std::string> _expression;
    std::stack<double> _stack;
    bool isOperand(std::string operand) { return (operand == "+" || operand == "-" || operand == "*" || operand == "/"); }
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

public:
    PostStringCalculater(std::string expression) {
        _expression = PostStringTransfer(expression).GetPostfixString();
    }
    double Calculate()
    {
        for (auto operand : _expression)
        {
            if (isOperand(operand))
            {
                auto number2 = _stack.top();
                _stack.pop();
                auto number1 = _stack.top();
                _stack.pop();

                try {
                    _stack.push(Calc(operand, number1, number2));
                }
                catch (std::runtime_error& e) {
                    std::cout << "Exception occurred" << std::endl<< e.what();
                    exit(0);
                }
            }
            else
            {
                _stack.push(std::stod(operand));
            }
        }

        return _stack.top();
    }
};