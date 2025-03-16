#pragma once
#include <sstream>
#include <iomanip>
#include"PostStringCalculater.hpp"
#include"PostStringTransfer.h"


class Function {
private:
	std::string _expression;
	Point _point;
	std::vector<std::string> vecOperand;
public:
	Function(std::string expression, Point point);
	double Calculate();
};

///////////////////////////////////////////////////////////////////////////////////

Function::Function(std::string expression, Point point) :
	_expression(expression),
	_point(point) {
		vecOperand = PostStringTransfer(_expression).GetPostfixString();
};

double Function::Calculate() {
	return PostStringCalculater(vecOperand, _point).Calculate();
}