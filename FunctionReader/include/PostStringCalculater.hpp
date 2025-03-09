#pragma once
#include"PostStringTransfer.h"
#include<iostream>


class PostStringCalculater{
    private:
    std::vector<std::string> vecExs;
    std::vector<double> vecPoint;
    std::stack<double> _stack;
    double decodeNumber(std::string number);

public:
    PostStringCalculater(std::vector<std::string> vecExpression, std::vector<double> vecPoint) : vecPoint(vecPoint){
        vecExs = PostStringTransfer(vecExpression).GetPostfixString();
    }

    double Calculate();
};

//////////////////////////////////////////////////////////////////////////
double PostStringCalculater::decodeNumber(std::string number){
    if(number.length() == 0){
        throw std::runtime_error("wrong in postfix _stack. Number hav not length");
    }

    if(number[0] != 'x'){
        return std::stod(number);
    }

    try {
        int index= std::stoi(number.substr(1)) - 1;
        if(index <0 || index >= vecPoint.size()) throw std::runtime_error("Invalid index " + number);
        else return vecPoint[index];
    }
    catch (const std::invalid_argument& ia) {
       throw std::runtime_error( "Invalid argument "  + number);
    }
    catch (const std::out_of_range& oor) {
        throw std::runtime_error( "Out of Range error: "  + number);
    }
}


double PostStringCalculater::Calculate(){
    for (auto operand : vecExs)
    {
        if (isOperation(operand))
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
            _stack.push(decodeNumber(operand));
        }
    }

    return _stack.top();
}