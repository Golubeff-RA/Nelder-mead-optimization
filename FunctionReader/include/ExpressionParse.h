#pragma once
#include"Algebra.h"


class expression_parser {
private:
    std::string expression_;
    std::vector<std::string> vecExpression_;
    std::string AddInList(std::string str, char symbol);
    void Parse();
    bool IsNeedSeparate(char symbol);
    void CheckScobCount();
public:
    expression_parser(std::string expression) : expression_(expression) {};
    std::vector<std::string> GetPraseExpression();
};

///////////////////////////////////////////////////////////////////////

std::string expression_parser::AddInList(std::string str, char symbol){
    if (str != "")
    {
        vecExpression_.push_back(str);
    }
    if (symbol != ' ') vecExpression_.push_back(std::string (1,symbol));
    str = "";
    return str;
}

void expression_parser::Parse(){
    std::string str = "";
    for (auto symbol : expression_)
    {
        if (IsNeedSeparate(symbol))
        {
            str = AddInList(str, symbol);
        }
        else str.push_back(symbol);
    }
    str = AddInList(str, ' ');
}

std::vector<std::string> expression_parser::GetPraseExpression()
{
    Parse();
    CheckScobCount();
    return vecExpression_;
}

bool expression_parser::IsNeedSeparate(char symbol){
    bool flag = false;
    flag |= symbol == ' ' || symbol == '(' || symbol == ')';
    //recognize -3, -5, -x
    if(IsOperation(symbol)){
        if(symbol == '-'){
            flag |= !(vecExpression_.size() == 0 || (IsOperation(vecExpression_.back()) || vecExpression_.back() == "(" || vecExpression_.back() == ")"));
        } else flag |= true;
    }
    return flag;
}

void expression_parser::CheckScobCount(){
    int scob_cnt = 0;
    for(auto e : vecExpression_){
        if(e == "(") {
            scob_cnt++;
        } else if(e == ")"){
            scob_cnt--;
        }
        if(scob_cnt < 0){
            throw std::runtime_error("Incorrect count sckob\n");
        }
    }
    if(scob_cnt > 0){
        throw std::runtime_error("Incorrect count sckob\n");
    }
}