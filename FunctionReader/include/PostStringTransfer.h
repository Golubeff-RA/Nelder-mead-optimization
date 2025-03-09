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

    void openScobActions(std::string str);
    void closeScobActions(std::string str);
    void operandActions(std::string str);
    void numberActions(std::string str);
    void FillPostfixstring();

public:
    PostStringTransfer(std::vector<std::string> vecExpression) :  _expression(vecExpression){}
    std::vector<std::string> GetPostfixString();
};



/////////////////////////////////////////////////////////////////////////////////
void PostStringTransfer::openScobActions(std::string str){
    _stack.push(str);
}

void PostStringTransfer::closeScobActions(std::string str){
    while (_stack.top() != "(")
    {
        _postExpression.push_back(_stack.top());
        _stack.pop();
    }
    _stack.pop();
}

void PostStringTransfer::operandActions(std::string str){
    while (!_stack.empty() && CheckOperandsMore(_stack.top(), str))
    {
        _postExpression.push_back(_stack.top());
        _stack.pop();
    }
    _stack.push(str);
}

void PostStringTransfer:: numberActions(std::string str){
    _postExpression.push_back(str);
}

void PostStringTransfer::FillPostfixstring(){
    for (auto str : _expression)
    {
        if (str == "(") openScobActions(str);
        else if (str == ")") closeScobActions(str);
        else if (isOperation(str)) operandActions(str);
        else numberActions(str);
    }

    while (!_stack.empty())
    {
        _postExpression.push_back(_stack.top());
        _stack.pop();
    }
}

std::vector<std::string> PostStringTransfer::GetPostfixString(){
    //new DataValidator().Check(_expression);
    //new ScobkaValidater().Check(_expression);

    FillPostfixstring();

    //new OperandValidator().Check(_postExpression);

    return _postExpression;
}