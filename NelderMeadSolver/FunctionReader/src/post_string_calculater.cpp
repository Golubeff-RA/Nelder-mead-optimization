#include "post_string_calculater.h"

namespace FR {
    double PostStringCalculater::DecodeNumber(const std::string& number) {
        bool isMinus = (number[0] == '-');
        if (constMap_.count(number.substr(isMinus))) {
            return constMap_[number.substr(isMinus)];
        }

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

    double PostStringCalculater::DecodeVar(const std::string& number, const Point& point) {
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

    double PostStringCalculater::Decode(const std::string& number, const Point& point) {
        if (number.length() == 0) {
            throw std::runtime_error("wrong in postfix stack_. Number have not length");
        }

        if (number[0] != 'x' && number[std::min(1, (int)number.size() - 1)] != 'x') {
           return DecodeNumber(number);
        }

        return DecodeVar(number, point);
    }

    double PostStringCalculater::Calculate(const Point& point) {
        for (auto operand : vecExs_) {
            if (IsOperation(operand)) {
                std::vector<double> vecNumber;
                switch (GetTypeOperation(operand)) {
                    case TYPE::BIN:
                        if (stack_.size() < 1) {
                            throw std::runtime_error("Incorrect expression\n");
                        }
                        vecNumber.push_back(stack_.top());
                        stack_.pop();
                        if (GetNameOperation(operand) == OPERAND::MINUS && (stack_.size() == 0 || IsOperation(stack_.top()))) {
                            stack_.push(Calc(operand, vecNumber));
                            break;
                        }
                    case TYPE::UNO:
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
                stack_.push(Decode(operand, point));
            }
        }

        return stack_.top();
    }
} // end FR