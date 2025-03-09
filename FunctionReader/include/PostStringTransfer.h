#pragma once
#include"ExpressionParse.h"
#include<map>
#include"Algebra.h"

class PostStringTransfer
{
private:
    std::vector<std::string> _expression;
    std::vector<std::string> _postExpression;
    std::stack<std::string> _stack;

    void openScobActions(std::string str)
    {
        _stack.push(str);
    }

    void closeScobActions(std::string str)
    {
        while (_stack.top() != "(")
        {
            _postExpression.push_back(_stack.top());
            _stack.pop();
        }
        _stack.pop();
    }

    void operandActions(std::string str)
    {
        while (!_stack.empty() && CheckOperandsMore(_stack.top(), str))
        {
            _postExpression.push_back(_stack.top());
            _stack.pop();
        }
        _stack.push(str);
    }

    void numberActions(std::string str)
    {
        _postExpression.push_back(str);
    }

    void FillPostfixstring()
    {
        for (auto str : _expression)
        {
            if (str == "(") openScobActions(str);
            else if (str == ")") closeScobActions(str);
            else if (isOperand(str)) operandActions(str);
            else numberActions(str);
        }

        while (!_stack.empty())
        {
            _postExpression.push_back(_stack.top());
            _stack.pop();
        }
    }

public:
    PostStringTransfer(std::vector<std::string> vecExpression) :  _expression(vecExpression){}

    std::vector<std::string> GetPostfixString()
    {
        //new DataValidator().Check(_expression);
        //new ScobkaValidater().Check(_expression);

        FillPostfixstring();

        //new OperandValidator().Check(_postExpression);

        return _postExpression;
    }
};