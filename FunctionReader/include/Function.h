#pragma once
#include <sstream>
#include <iomanip>
#include"PostStringCalculater.hpp"


class Function {
private:
	std::string expression;
	std::vector<double> vecPoint;
	void ChangeByPos(size_t ind);
	void DecodeIndex(size_t pos, std::string& ind);
	std::string ConvertToString(const double& x, const int precision);
public:
	Function(std::string expression, std::vector<double> vecPoint);
	void Decode();
	void Print();
	double Calculate();
};