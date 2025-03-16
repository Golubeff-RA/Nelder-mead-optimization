#pragma once
#include"Algebra.h"
#include<stack>
#include<iostream>


class PostStringCalculater{
    private:
    std::vector<std::string> vecExs;
    Point _point;
    std::stack<double> _stack;
    double decodeNumber(std::string number);

public:
    PostStringCalculater(std::vector<std::string> vecExpression, Point point) : 
        vecExs(vecExpression),
        _point(point){}

    double Calculate();
};

//////////////////////////////////////////////////////////////////////////
double PostStringCalculater::decodeNumber(std::string number){
    if(number.length() == 0){
        throw std::runtime_error("wrong in postfix _stack. Number have not length");
    }

    if(number[0] != 'x' && number[std::min(1, (int)number.size() - 1)] != 'x'){
        return std::stod(number);
    }

    try {
        bool isMinus = (number[0] == '-');
        int index= std::stoi(number.substr(1 + (isMinus))) - 1;
        /////////////////////////////////
        if(index < 0 || index >= (int)_point.Size()) throw std::runtime_error("Invalid index " + number);
        else return _point[index] * (isMinus ? -1 : 1);
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
            if(_stack.size() < 2){
                throw std::runtime_error("Incorrect expression\n");
            }
            auto number2 = _stack.top();
            _stack.pop();
            auto number1 = _stack.top();
            _stack.pop();

            _stack.push(Calc(operand, number1, number2));
        }
        else
        {
            _stack.push(decodeNumber(operand));
        }
    }

    return _stack.top();
}