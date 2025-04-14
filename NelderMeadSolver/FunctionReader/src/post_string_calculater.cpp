#include "post_string_calculater.h"

double PostStringCalculater::DecodeNumber(std::string number, Point& point) {
    if (number.length() == 0) {
        throw std::runtime_error("wrong in postfix stack_. Number have not length");
    }

    if (number[0] != 'x' && number[std::min(1, (int)number.size() - 1)] != 'x') {
        try {
            size_t parse_number = 0;
            double ans = std::stod(number, &parse_number);
            if (parse_number != number.size()) {
                throw std::runtime_error("Invalid number " + number);
            } else {
                return ans;
            }
        } catch (const std::invalid_argument& ia) {
            throw std::runtime_error("Invalid argument " + number);
        } catch (const std::out_of_range& oor) {
            throw std::runtime_error("Out of Range error: " + number);
        }
    }

    try {
        bool isMinus = (number[0] == '-');
        size_t parse_number = 0;
        int index = std::stoi(number.substr(1 + (isMinus)), &parse_number) - 1;
        /////////////////////////////////
        if (index < 0 || index >= (int)point.Size() || parse_number != number.size() - 1 - isMinus) {
            throw std::runtime_error("Invalid index " + number);
        } else {
            return point[index] * (isMinus ? -1 : 1);
        }
    } catch (const std::invalid_argument& ia) {
        throw std::runtime_error("Invalid argument " + number);
    } catch (const std::out_of_range& oor) {
        throw std::runtime_error("Out of Range error: " + number);
    }
}

double PostStringCalculater::Calculate(Point& point) {
    for (auto operand : vecExs_) {
        if (IsOperation(operand)) {
            std::vector<double> vecNumber;
            switch (GetTypeOperation(operand)) {
                case BIN:
                    if (stack_.size() < 2) {
                        throw std::runtime_error("Incorrect expression\n");
                    }
                    vecNumber.push_back(stack_.top());
                    stack_.pop();
                    vecNumber.push_back(stack_.top());
                    stack_.pop();
                    stack_.push(Calc(operand, vecNumber));
                    break;
                case UNO:
                    if (stack_.size() < 1) {
                        throw std::runtime_error("Incorrect expression\n");
                    }
                    vecNumber.push_back(stack_.top());
                    stack_.pop();
                    stack_.push(Calc(operand, vecNumber));
                    break;
                default:
                    throw std::runtime_error("Incorrect operation type\n");
            }
        } else {
            stack_.push(DecodeNumber(operand, point));
        }
    }

    return stack_.top();
}