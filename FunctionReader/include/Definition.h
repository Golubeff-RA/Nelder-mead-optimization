#include<stack>
#include<iostream>
#include<map>
#include<string>
#include<math.h>
#include<cmath>
#include <sstream>
#include <iomanip>

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

struct Operation{
    int name_;
    int priority_;
    int typeOperation_;
    Operation() { name_ = -2; priority_ = -2; typeOperation_ = -2;}
    Operation(int name, int priority, int typeOperation) : name_(name), priority_(priority), typeOperation_(typeOperation){}
};

std::map<std::string, Operation> operationMap_ = {
    { "()", Operation(SCOBKA, 0, NONE) },
    { ")", Operation(SCOBKA, 0, NONE) },
    { "+", Operation(PLUS, 1, BIN) },
    { "-", Operation(MINUS, 2, BIN) },
    { "*", Operation(MULT, 3, BIN) },
    { "/", Operation(DIVIDER, 3, BIN)},
    { "^", Operation(POWER, 4, BIN)},
    { "sin", Operation(SIN, 5, UNO)},
    { "cos", Operation(COS, 5, UNO)},
    { "tan", Operation(TAN, 5, UNO)},
    { "ctg", Operation(CTG, 5, UNO)},
    { "ln", Operation(LN, 5, UNO)},
    { "log2", Operation(LOG2, 5, UNO)},
    { "log", Operation(LOG, 5, UNO)},
    { "sqrt", Operation(SQRT, 5, UNO)},
    { "abs", Operation(ABS, 5, UNO)}
};

