#pragma once
#include "algebra.h"

class expression_parser {
private:
    std::string expression_;
    std::vector<std::string> vecExpression_;
    std::string AddInList(std::string str, char symbol);
    void Parse();
    bool IsNeedSeparate(char symbol);
    void CheckScobCount();

public:
    expression_parser(std::string expression) : expression_(expression){};
    std::vector<std::string> GetPraseExpression();
};
