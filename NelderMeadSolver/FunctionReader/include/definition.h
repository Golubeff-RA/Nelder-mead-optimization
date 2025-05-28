#pragma once
#include <math.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <cstdint> 

namespace FR {
    enum class OPERAND{
        NONE, SCOBKA, PLUS, MINUS,
        MULT, DIVIDER, POWER,
        SIN, COS, TAN,
        CTG, LN, LOG2,
        LOG, SQRT, ABS
    };

    enum class TYPE {
        NONE, UNO, BIN
    };

    inline std::map<std::string, double> constMap_ {
        {"e", std::exp(1.0)},
        {"pi", std::acos(-1)}
    };

    struct Operation {
        OPERAND name_;
        int priority_;
        TYPE typeOperation_;
        Operation(){
            name_ = OPERAND::NONE;
            priority_ = INT32_MIN;
            typeOperation_ = TYPE::NONE;
        }
        Operation(OPERAND name, int priority, TYPE typeOperation)
            : name_(name), priority_(priority), typeOperation_(typeOperation) {
        }
    };
} // end FR

