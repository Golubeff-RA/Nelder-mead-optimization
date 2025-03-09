#pragma once
#include <sstream>
#include <iomanip>
#include"PostStringCalculater.hpp"


class Function {
private:
	std::string expression;
	std::vector<double> vecPoint;
	std::vector<std::string> vecOperand;
public:
	Function(std::string expression, std::vector<double> vecPoint);
	double Calculate();
};

///////////////////////////////////////////////////////////////////////////////////

Function::Function(std::string expression, std::vector<double> vecPoint) :
	expression(expression),
	vecPoint(vecPoint) {
		vecOperand = ExpressionParser(expression).GetPraseExpression();
};

double Function::Calculate() {
	return PostStringCalculater(vecOperand, vecPoint).Calculate();
}