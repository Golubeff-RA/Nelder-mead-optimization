#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include"Algebra.h"


class ExpressionParser {
private:
    std::string _expression;
    std::vector<std::string> list_expression;
    std::string AddInList(std::string str, char symbol);
    void Parse();

public:
    ExpressionParser(std::string expression) : _expression(expression) {};
    std::vector<std::string> GetPraseExpression();
};

///////////////////////////////////////////////////////////////////////

std::string ExpressionParser::AddInList(std::string str, char symbol){
    if (str != "")
    {
        list_expression.push_back(str);
    }
    if (symbol != ' ') list_expression.push_back(std::string (1,symbol));
    str = "";
    return str;
}

void ExpressionParser::Parse(){
    std::string str = "";
    for (auto symbol : _expression)
    {
        if (symbol == ' ' || symbol == '(' || symbol == ')' || isOperation(symbol))
        {
            str = AddInList(str, symbol);
        }
        else str.push_back(symbol);
    }
    str = AddInList(str, ' ');
}

std::vector<std::string> ExpressionParser::GetPraseExpression()
{
    Parse();
    return list_expression;
}