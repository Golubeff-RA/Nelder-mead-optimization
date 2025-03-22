#pragma once
#include"Algebra.h"


class PostStringCalculater{
    private:
    std::vector<std::string> vecExs_;
    std::stack<double> stack_;
    double DecodeNumber(std::string number, Point &point);

public:
    PostStringCalculater(std::vector<std::string> vecExpression) : 
        vecExs_(vecExpression){}

    double Calculate(Point& point);
};

//////////////////////////////////////////////////////////////////////////
double PostStringCalculater::DecodeNumber(std::string number, Point& point){
    if(number.length() == 0){
        throw std::runtime_error("wrong in postfix stack_. Number have not length");
    }

    if(number[0] != 'x' && number[std::min(1, (int)number.size() - 1)] != 'x'){
        try{
            return std::stod(number);
        } catch (const std::invalid_argument& ia) {
            throw std::runtime_error( "Invalid argument "  + number);
        } catch (const std::out_of_range& oor) {
            throw std::runtime_error( "Out of Range error: "  + number);
        }
    }

    try {
        bool isMinus = (number[0] == '-');
        int index= std::stoi(number.substr(1 + (isMinus))) - 1;
        /////////////////////////////////
        if(index < 0 || index >= (int)point.Size()) throw std::runtime_error("Invalid index " + number);
        else return point[index] * (isMinus ? -1 : 1);
    }
    catch (const std::invalid_argument& ia) {
       throw std::runtime_error( "Invalid argument "  + number);
    }
    catch (const std::out_of_range& oor) {
        throw std::runtime_error( "Out of Range error: "  + number);
    }
}


double PostStringCalculater::Calculate(Point& point){
    for (auto operand : vecExs_)
    {
        if (IsOperation(operand))
        {
            if(stack_.size() < 2){
                throw std::runtime_error("Incorrect expression\n");
            }
            auto number2 = stack_.top();
            stack_.pop();
            auto number1 = stack_.top();
            stack_.pop();

            stack_.push(Calc(operand, number1, number2));
        }
        else
        {
            stack_.push(DecodeNumber(operand, point));
        }
    }

    return stack_.top();
}