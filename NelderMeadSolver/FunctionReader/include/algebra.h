#pragma once
#include "definition.h"
#include "point.h"

int GetTypeOperation(std::string operand);

bool CheckOperandsMore(std::string operand1, std::string operand2);

bool IsOperation(std::string operand);

bool IsOperation(char operand);

double Calc(std::string operation, std::vector<double>& vecNumber);