#pragma once
#include"ExpressionParse.h"
#include"Algebra.h"

class PostStringTransfer
{
private:
    std::vector<std::string> expression_;
    std::vector<std::string> postExpression_;
    std::stack<std::string> stack_;

    void OpenScobActions(std::string str);
    void CloseScobActions(std::string str);
    void OperandActions(std::string str);
    void NumberActions(std::string str);
    void FillPostfixstring();

public:
    //PostStringTransfer(std::vector<std::string> vecExpression) :  expression_(vecExpression){}
    PostStringTransfer(std::string expression);
    std::vector<std::string> GetPostfixString();
};



/////////////////////////////////////////////////////////////////////////////////
PostStringTransfer::PostStringTransfer(std::string expression){
    expression_ = expression_parser(expression).GetPraseExpression();
}
void PostStringTransfer::OpenScobActions(std::string str){
    stack_.push(str);
}

void PostStringTransfer::CloseScobActions(std::string str){
    while (stack_.top() != "(")
    {
        postExpression_.push_back(stack_.top());
        stack_.pop();
    }
    stack_.pop();
}

void PostStringTransfer::OperandActions(std::string str){
    while (!stack_.empty() && CheckOperandsMore(stack_.top(), str))
    {
        postExpression_.push_back(stack_.top());
        stack_.pop();
    }
    stack_.push(str);
}

void PostStringTransfer:: NumberActions(std::string str){
    postExpression_.push_back(str);
}

void PostStringTransfer::FillPostfixstring(){
    for (auto str : expression_)
    {
        if (str == "(") OpenScobActions(str);
        else if (str == ")") CloseScobActions(str);
        else if (IsOperation(str)) OperandActions(str);
        else NumberActions(str);
    }

    while (!stack_.empty())
    {
        postExpression_.push_back(stack_.top());
        stack_.pop();
    }
}

std::vector<std::string> PostStringTransfer::GetPostfixString(){
    FillPostfixstring();
    return postExpression_;
}