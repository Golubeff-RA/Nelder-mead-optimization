#pragma once
#include <math.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>

#define SCOBKA -1
#define PLUS 0
#define MINUS 1
#define MULT 3
#define DIVIDER 4
#define POWER 5
#define SIN 6
#define COS 7
#define TAN 8
#define CTG 9
#define LN 10
#define LOG2 11
#define LOG 12
#define SQRT 13
#define ABS 14

#define NONE 0
#define UNO 1
#define BIN 2

struct Operation {
    int name_;
    int priority_;
    int typeOperation_;
    Operation() {
        name_ = -2;
        priority_ = -2;
        typeOperation_ = -2;
    }
    Operation(int name, int priority, int typeOperation)
        : name_(name), priority_(priority), typeOperation_(typeOperation) {
    }
};

